/*
    A client who is recieving and sending seed.
*/

#pragma once

#include <string>
#include <netinet/in.h>
#include <mutex>

class Client
{
public:
    Client(const std::string& address, int port);
    ~Client();

    void init();
    void connectToServer();
    void sendSeeds(const std::string& message);

    const std::string& getAddress() const;
    int getPort() const;

private:
    int sockfd;
    int port;
    std::string address;
    sockaddr_in client;
    std::mutex mutex;
};

class ConnectClientException {};
