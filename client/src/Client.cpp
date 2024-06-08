//
// Created by Pranay on 6/8/2024.
//

#include "Client.h"

Client::Client(const std::string &ip, int port) : clientSocket(INVALID_SOCKET) {
    clientService.sin_family = AF_INET;
    InetPton(AF_INET, ip.c_str(), &clientService.sin_addr);
    clientService.sin_port = htons(port);
}

Client::~Client() {
    closesocket(clientSocket);
    WSACleanup();
}

void Client::start() {
    initializeWinSock();
    createSocket();
    connectToServer();
}

void Client::initializeWinSock() {
    WSADATA wsaData;
    auto mVersionRequested = MAKEWORD(2, 2);
    int wsaErr = WSAStartup(mVersionRequested, &wsaData);
    if (wsaErr != 0) {
        std::cerr << "Winsock dll not found!" << std::endl;
        exit(1);
    }
}

void Client::createSocket() {
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error at Socket creation" << std::endl;
        WSACleanup();
        exit(1);
    }
}

void Client::connectToServer() {
    auto connection = connect(clientSocket, reinterpret_cast<const sockaddr *>(&clientService), sizeof(clientService));
    if (connection == SOCKET_ERROR) {
        std::cerr << "connection failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(1);
    }
    std::cout << "Connected to server!" << std::endl;
}

void Client::playGame() {
    while (true) {
        RPSChoice clientChoice = getRandomChoice();
        std::string clientChoiceStr = GameUtils::toString(clientChoice);
        send(clientSocket, clientChoiceStr.c_str(), clientChoiceStr.size(), 0);

        char receivedBuffer[512];
        int result = recv(clientSocket, receivedBuffer, sizeof(receivedBuffer), 0);
        if (result > 0) {
            receivedBuffer[result] = '\0';
            std::cout << "Result: " << receivedBuffer <<std::endl;
        } else if (result == 0) {
            std::cout << "Connection closing...\n";
            closesocket(clientSocket);
            break;
        } else {
            std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

RPSChoice Client::getRandomChoice() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,2);
    return static_cast<RPSChoice>(dis(gen));
}
