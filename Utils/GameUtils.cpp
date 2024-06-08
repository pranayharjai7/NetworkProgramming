//
// Created by Pranay on 6/8/2024.
//

#include "GameUtils.h"

const std::unordered_map<std::string, RPSChoice> GameUtils::strToEnumMap = {
        {"ROCK",     RPSChoice::ROCK},
        {"PAPER",    RPSChoice::PAPER},
        {"SCISSORS", RPSChoice::SCISSORS}
};

RPSChoice GameUtils::getRandChoice() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);
    return static_cast<RPSChoice>(dis(gen));
}

std::string GameUtils::toString(RPSChoice choice) {
    switch (choice) {
        case RPSChoice::ROCK:
            return "ROCK";
        case RPSChoice::PAPER:
            return "PAPER";
        case RPSChoice::SCISSORS:
            return "SCISSORS";
        default:
            return "UNKNOWN";
    }
}

RPSChoice GameUtils::toEnum(const std::string &str) {
    auto it = strToEnumMap.find(str);
    if (it != strToEnumMap.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Invalid string for RPSChoice enum");
    }
}
