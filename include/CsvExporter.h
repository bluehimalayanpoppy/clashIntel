#pragma once

#include "Battle.h"
#include <string>
#include <vector>

class CsvExporter
{
public:
    static bool exportBattles(
        const std::vector<Battle>& battles,
        const std::string& filename
    );
};