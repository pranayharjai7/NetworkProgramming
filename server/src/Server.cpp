//
// Created by Pranay on 6/8/2024.
//

#include "Server.h"

Server::Server(const std::string &ip, int port) : serverSocket(INVALID_SOCKET), clientId(0) {
    service.sin_family = AF_INET;
    InetPton(AF_INET, ip.c_str(), &service.sin_addr);
    service.sin_port = htons(port);
}

Server::~Server() {
    closesocket(serverSocket);
    WSACleanup();
}

void Server::start() {
    initializeWinSock();
    createSocket();
    bindSocket();
    listenOnSocket();

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }
        std::cout << "Accepted connection" << std::endl;
        std::thread clientThread(&ClientHandler::handleClient, clientSocket, clientId++);
        clientThread.detach();
    }
}

void Server::initializeWinSock() {
    WSADATA wsaData;
    auto mVersionRequested = MAKEWORD(2, 2);
    int wsaErr = WSAStartup(mVersionRequested, &wsaData);
    if (wsaErr != 0) {
        std::cerr << "Winsock dll not found!" << std::endl;
        exit(1);
    }
}

void Server::createSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);   //socket for tcp connection
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error at Socket creation" << std::endl;
        WSACleanup();
        exit(1);
    }
}

void Server::bindSocket() {
    auto bound = bind(serverSocket, reinterpret_cast<const sockaddr *>(&service), sizeof(service));
    if (bound == SOCKET_ERROR) {
        std::cerr << "binding failed!" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        exit(1);
    }
}

void Server::listenOnSocket() const {
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error listening on socket: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        exit(1);
    }

    std::cout << "Server is listening on port 5001..." << std::endl;
}
