#include <iostream>
#include <winsock.h>
#include <ws2tcpip.h>

int main(int argc, char *argv[]) {
    // setup dll
    WSADATA wsaData;
    auto mVersionRequested = MAKEWORD(2,2);
    int wsaErr = WSAStartup(mVersionRequested, &wsaData);
    if (wsaErr != 0) {
        std::cerr << "Winsock dll not found!" << std::endl;
        return 0;
    } else {
        std::cout << "Winsock status: " << wsaData.szSystemStatus << std::endl;
    }

    //Setting client socket
    auto clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error at Socket creation" << std::endl;
        WSACleanup();
        return 0;
    } else {
        std::cout << "socket is OK!" << std::endl;
    }

    //Bind with server ip and port
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPton(AF_INET, "127.0.0.1", &clientService.sin_addr);
    clientService.sin_port = htons(5001);

    //connect to server
    auto connection = connect(clientSocket, reinterpret_cast<const sockaddr *>(&clientService), sizeof(clientService));
    if (connection == SOCKET_ERROR) {
        std::cerr << "connection failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    } else {
        std::cerr << "Client: Connected! " << std::endl;
    }

    system("pause");
    WSACleanup();
    return 0;
}
