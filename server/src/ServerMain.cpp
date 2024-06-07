#include <iostream>
#include <winsock.h>
#include <ws2tcpip.h>

int main(int argc, char *argv[]) {

    //Initializing WinSock
    WSADATA wsaData;
    auto mVersionRequested = MAKEWORD(2, 2);
    int wsaErr = WSAStartup(mVersionRequested, &wsaData);
    if (wsaErr != 0) {
        std::cerr << "Winsock dll not found!" << std::endl;
        return 1;
    }

    //Setting up server socket
    auto serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);   //socket for tcp connection
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error at Socket creation" << std::endl;
        WSACleanup();
        return 1;
    }

    //Binding Ip and port to socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, "127.0.0.1", &service.sin_addr);
    service.sin_port = htons(5001);
    auto bound = bind(serverSocket, reinterpret_cast<const sockaddr *>(&service), sizeof(service));
    if (bound == SOCKET_ERROR) {
        std::cerr << "binding failed!" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    //Listen on socket
    auto answer = listen(serverSocket, 1);
    if (answer == SOCKET_ERROR) {
        std::cerr << "Error listening on socket: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port 5001..." << std::endl;

    //Accept connection
    SOCKET acceptSocket = accept(serverSocket, nullptr, nullptr);
    if (acceptSocket == INVALID_SOCKET) {
        std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }
    std::cout << "Accepted connection" << std::endl;
    system("pause");
    WSACleanup();

    return 0;
}
