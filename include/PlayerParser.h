#pragma once
#include "Player.h"
#include <string>


class PlayerParser
{
public:

    //takes raw player JSON string from Clash API
    //converts JSON data into a Player object
    Player parsePlayer(const std::string& jsonData);

};