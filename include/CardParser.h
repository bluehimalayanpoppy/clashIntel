#pragma once

#include <string>
#include <vector>
#include "Card.h"

class CardParser
{
public:
    std::vector<Card> parseCards(const std::string& json);
};