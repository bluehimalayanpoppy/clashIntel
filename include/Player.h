#pragma once

#include <string>
#include <vector>

class Player
{
public:
    std::string name;
    int totalTrophies;
    std::vector<std::string> currentDeck;
    Player();
};