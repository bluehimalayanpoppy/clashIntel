#include <iostream>
#include <cstdlib>
#include "ClashClient.h"
#include "BattleParser.h"
#include "CsvExporter.h"


int main(int argc, char ** argv)
{

    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <player_tag>\n";
        return 1;
    }



    //gets API token from environment variable
    const char* token = std::getenv("CLASH_API_TOKEN");
    if (!token)
    {
        std::cerr << "Error: set CLASH_API_TOKEN environment variable\n";
        return 1;
    }

    //creates API client
    ClashClient client(token);

    //gets raw battle log JSON from Clash API
    std::string battleData = client.getBattleLog(argv[1]);

    //creates parser object
    BattleParser parser;

    //converts JSON string into Battle objects
    std::vector<Battle> battles =
        parser.parseBattles(battleData);


    //prints every battle to confirm data was converted
    for (const auto& battle : battles)
    {

        std::cout << "---------------------\n";


        if (battle.won)
        {
            std::cout << "Result: WIN\n";
        }
        else
        {
            std::cout << "Result: LOSS\n";
        }



        std::cout << "My trophies: " << battle.myTrophies << "\n";


        std::cout << "Opponent trophies: " << battle.opponentTrophies << "\n";

        std::cout << "Crowns: " << battle.myCrowns << " - " << battle.opponentCrowns << "\n";

        std::cout << "My average card level: " << battle.myAverageCardLevel << "\n";

        std::cout << "My deck:\n";


        for (const auto& card : battle.myDeck)
        {
            std::cout << "  " << card << "\n";
        }

    }

    //writes battles to csv file
    if (CsvExporter::exportBattles(battles, "data/battles.csv"))
    {
    std::cout << "battles exported successfully\n";
    }
}