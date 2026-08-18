#pragma once

#include <string>
#include <vector>

class Player
{
public:
    std::string name;
    int trophies;
    int bestTrophies;
    
    std::vector<std::string> currentDeck;
    Player();
};