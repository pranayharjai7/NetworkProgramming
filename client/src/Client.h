//
// Created by Pranay on 6/8/2024.
//

#ifndef NETWORKPROGRAMMING_CLIENT_H
#define NETWORKPROGRAMMING_CLIENT_H

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include "../../Utils/GameUtils.h"
#include <random>

class Client {
private:
    SOCKET clientSocket;
    sockaddr_in clientService{};

    void initializeWinSock();
    void createSocket();
    void connectToServer();
    static RPSChoice getRandomChoice();

public:
    Client(const std::string &ip, int port);
    ~Client();
    void start();
    void playGame();
};

#endif //NETWORKPROGRAMMING_CLIENT_H
