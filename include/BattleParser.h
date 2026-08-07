#pragma once
#include "Battle.h"

#include <string>
#include <vector>

class BattleParser
{

public:

    //takes raw json string from Clash API
    //converts JSON data into Battle objects
    std::vector<Battle> parseBattles(const std::string& jsonData);

};