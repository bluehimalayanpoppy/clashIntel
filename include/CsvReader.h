#pragma once

#include <string>
#include <vector>
#include "Battle.h"

class CsvReader
{
public:

    //reads battles from csv
    static std::vector<Battle> readBattles(const std::string& filename
    );
};