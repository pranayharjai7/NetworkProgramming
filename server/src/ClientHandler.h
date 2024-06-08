//
// Created by Pranay on 6/8/2024.
//

#ifndef NETWORKPROGRAMMING_CLIENTHANDLER_H
#define NETWORKPROGRAMMING_CLIENTHANDLER_H

#include <string>
#include <iostream>
#include <random>
#include <winsock2.h>
#include <unordered_map>
#include <mutex>
#include "../../Utils/GameUtils.h"

class ClientHandler {
public:
    static void handleClient(SOCKET clientSocket, int clientId);
};


#endif //NETWORKPROGRAMMING_CLIENTHANDLER_H
