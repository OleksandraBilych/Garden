#pragma once

#include <memory>

#include "client.h"

class AppServer
{
public:
    AppServer(int port);
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
    int port;
    int sockfd;
    sockaddr_in address;
    std::unique_ptr<Client> client;

    void addClient();
    // add clients

};

class SocketCreationException {};
class SocketSetOptionsException {};
class SocketBindException {};
