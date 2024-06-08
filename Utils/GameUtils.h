//
// Created by Pranay on 6/8/2024.
//

#ifndef NETWORKPROGRAMMING_GAMEUTILS_H
#define NETWORKPROGRAMMING_GAMEUTILS_H

#include <string>
#include <unordered_map>
#include <stdexcept>
#include <random>

enum class RPSChoice {
    ROCK = 0,
    PAPER = 1,
    SCISSORS = 2

};

class GameUtils {
private:
    static const std::unordered_map<std::string, RPSChoice> strToEnumMap;
public:
    static RPSChoice getRandChoice();
    static std::string toString(RPSChoice choice);
    static RPSChoice toEnum(const std::string &str);
};


#endif //NETWORKPROGRAMMING_GAMEUTILS_H
