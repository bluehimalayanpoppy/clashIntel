#include "CsvReader.h"

#include <fstream>
#include <iostream>
#include <sstream>

//reads battles from csv
std::vector<Battle> CsvReader::readBattles(
    const std::string& filename)
{
    std::vector<Battle> battles;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: could not open CSV file\n";
        return battles;
    }

    std::string line;

    //skip header
    std::getline(file, line);

    //reads each battle
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string value;
        Battle battle;

        //won
        std::getline(ss, value, ',');
        battle.won = (value == "1");

        //my trophies
        std::getline(ss, value, ',');
        battle.myTrophies = std::stoi(value);

        //opponent trophies
        std::getline(ss, value, ',');
        battle.opponentTrophies = std::stoi(value);

        //my crowns
        std::getline(ss, value, ',');
        battle.myCrowns = std::stoi(value);
        //my deck
        std::getline(ss, value, ',');

        std::stringstream myDeckStream(value);
        std::string card;

        while (std::getline(myDeckStream, card, '|'))
        {
            if (!card.empty())
            {
                battle.myDeck.push_back(card);
            }
        }
        //opponent deck
        std::getline(ss, value, ',');

        std::stringstream opponentDeckStream(value);

        while (std::getline(opponentDeckStream, card, '|'))
        {
            if (!card.empty())
            {
                battle.opponentDeck.push_back(card);
            }
        }

        //my average card level
        std::getline(ss, value, ',');
        battle.myAverageCardLevel = std::stod(value);
        //opponent average card level
        std::getline(ss, value, ',');
        battle.opponentAverageCardLevel = std::stod(value);

        battles.push_back(battle);
    }
    return battles;
}