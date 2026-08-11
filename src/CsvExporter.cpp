#include <fstream>
#include <iostream>
#include "CsvExporter.h"
#include "Battle.h"

//0: loss 1: win
bool CsvExporter::exportBattles(
    const std::vector<Battle>& battles,
    const std::string& filename
)
{
    //opens the csv file for writing
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: could not open csv file\n";
        return false;
    }

    //writes the csv header
    file << "won,my_trophies,opponent_trophies,my_crowns,opponent_crowns,my_deck,opponent_deck,my_average_card_level,opponent_average_card_level\n";

    //writes each battle to the csv file
    for (const auto& battle : battles)
    {
        file << battle.won << ","
             << battle.myTrophies << ","
             << battle.opponentTrophies << ","
             << battle.myCrowns << ",";
            
    
         //for one battle get the decks
            for (const auto& card: battle.myDeck)
            {
                file << card << "|";
            }
            file << ",";
            for (const auto& opponentCard: battle.opponentDeck)
            {
                file << opponentCard << "|";
            }
            file << ","

            << battle.myAverageCardLevel << ","
            << battle.opponentAverageCardLevel << "\n";
    }
    

    return true;
}