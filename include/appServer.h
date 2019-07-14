#pragma once

#include <memory>
#include <thread>
#include <mutex>

#include "client.h"
#include "farmer.h"

class AppServer
{
public:
    AppServer(int port, unsigned sendingFrequency);
    AppServer(const AppServer& engine) = delete; 
    AppServer(AppServer&& engine) noexcept = delete;

    AppServer& operator=(const AppServer& engine) = delete;
    AppServer& operator=(AppServer&& engine) noexcept = delete;

    ~AppServer();

    void init();

    void start();
    void stop();   
    void restart();

private:
    bool isRunning;
    std::mutex serverStatus;
    sockaddr_in address;
    int port;
    int sockfd;
    std::unique_ptr<Client> client;
    std::thread sendingThread;
    unsigned sendingFrequency;
    std::unique_ptr<Farmer> farmer;

    void sendingControl();
    void addClient();
};

class SocketCreationException {};
class SocketSetOptionsException {};
class SocketBindException {};
