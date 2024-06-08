//
// Created by Pranay on 6/8/2024.
//

#include "ClientHandler.h"


void ClientHandler::handleClient(SOCKET clientSocket, int clientId) {
    char receivedBuffer[512];
    int result;

    while (true) {
        result = recv(clientSocket, receivedBuffer, sizeof(receivedBuffer), 0);
        if (result > 0) {
            receivedBuffer[result] = '\0';
            std::string clientChoiceStr(receivedBuffer);
            RPSChoice clientChoice = GameUtils::toEnum(clientChoiceStr);
            RPSChoice serverChoice = GameUtils::getRandChoice();
            std::string resultMessage;

            if (clientChoice == serverChoice) {
                resultMessage = "draw";
            } else if ((clientChoice == RPSChoice::ROCK && serverChoice == RPSChoice::SCISSORS) ||
                       (clientChoice == RPSChoice::SCISSORS && serverChoice == RPSChoice::PAPER) ||
                       (clientChoice == RPSChoice::PAPER && serverChoice == RPSChoice::ROCK)) {
                resultMessage = "win";
            } else {
                resultMessage = "lose";
            }

            resultMessage += " Server choice: " + GameUtils::toString(serverChoice);
            send(clientSocket, resultMessage.c_str(), resultMessage.size(), 0);
        } else if (result == 0) {
            std::cout << "Connection closing...\n";
            closesocket(clientSocket);
            break;
        } else {
            std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
            closesocket(clientSocket);
            break;
        }
    }
}



