#pragma once

#include <string>

class Card
{
    //card specific data
public:
    std::string name;
    int id;
    int elixirCost;
    int maxLevel;
    int maxEvolutionLevel;
    std::string rarity;
};