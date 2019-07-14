#include "appServer.h"
#include "globalVariables.h"
#include "objectConverter.hpp"
#include "log.h"

#include <fstream>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <chrono>

AppServer::AppServer(int port, unsigned sendingFrequency)
    : port {port}, sendingFrequency {sendingFrequency}, isRunning {false}
{
    farmer.reset(new Farmer(globVar::farmerName, globVar::farmersWater));
    init();
    addClient();
}

AppServer::~AppServer()
{
    stop();

    close(sockfd);

    if (sendingThread.joinable()) {
        sendingThread.join();
    }
}

void AppServer::init()
{
    int opt {1};
    timeval timout {0, 100};

    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timout, sizeof(timout)) < 0) {
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    }

    bzero((char *) &address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY); 
    address.sin_port = htons(port);
       
    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }

    PRINT("Server initialized");
}

void AppServer::start()
{
    if (isRunning) {
        return;
    }
    
    {
        std::lock_guard<std::mutex> lck (serverStatus);
        isRunning = true;
    }

    PRINT("Creatind sending thread");
    sendingThread = std::thread(&AppServer::sendingControl, this);
    sendingThread.join();
}

void AppServer::stop()
{
    if (isRunning) {
        std::lock_guard<std::mutex> lck (serverStatus);

        isRunning = false;
    }
}

void AppServer::restart()
{
    stop();
    start();
}

void AppServer::addClient()
{
    PRINT("Adding client...");

    std::ifstream init;
    json cl;

    try {
        init.open(globVar::initSettingsFile, std::ifstream::in);
    } catch (std::ios_base::failure& e) {
        PRINT(e.what());
    }

    init >> cl;
    auto [ip, port] = Converter::toAddrAndPort(cl.at("client"));

    client.reset(new Client(ip, port));

    PRINT("Client added");
}

void AppServer::sendingControl()
{
    for (int msgNumber = 1; isRunning && msgNumber <= 3; ++msgNumber) {
        client->sendSeeds(farmer->getSeed());

        std::this_thread::sleep_for (std::chrono::seconds(sendingFrequency));
    }
}