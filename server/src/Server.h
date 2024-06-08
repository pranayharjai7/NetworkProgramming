//
// Created by Pranay on 6/8/2024.
//

#ifndef NETWORKPROGRAMMING_SERVER_H
#define NETWORKPROGRAMMING_SERVER_H

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include "ClientHandler.h"

class Server {
private:
    SOCKET serverSocket;
    sockaddr_in service{};
    int clientId;

    static void initializeWinSock();
    void createSocket();
    void bindSocket();
    void listenOnSocket() const;

public:
    Server(const std::string &ip, int port);
    ~Server();
    void start();
};


#endif //NETWORKPROGRAMMING_SERVER_H
