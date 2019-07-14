#include "client.h"
#include "log.h"

#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


Client::Client(const std::string& address, int port)
    : address(address), port(port)
{
    init();
}

Client::~Client()
{
    close(sockfd);
}

void Client::init()
{
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }

    bzero((char*) &client, sizeof(client));
    client.sin_family = AF_INET;
    inet_pton(AF_INET, address.c_str(), &(client.sin_addr));
    client.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr*) &client, sizeof(client)) < 0) {
        perror("connect"); 
        exit(EXIT_FAILURE); 
    }
}

void Client::sendSeeds(const std::string& message)
{
    std::lock_guard<std::mutex> lock(mutex);

    if (send(sockfd, message.c_str(), strlen(message.c_str()), 0) < 0) {
        perror("send"); 
        exit(EXIT_FAILURE); 
    }
}

const std::string& Client::getAddress() const
{
    return address;
}

int Client::getPort() const
{
    return port;
}
