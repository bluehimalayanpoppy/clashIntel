#include <iostream>
#include <cstdlib>
#include <fstream> 
#include <string>
#include "ClashClient.h"
#include "BattleParser.h"
#include "CsvExporter.h"
#include "PlayerParser.h"
#include "CardParser.h"


//loads variables from the .env file
void loadEnv(const std::string& filename)
{

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: could not open .env file\n";
        return;
    }

    std::string line;

   
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        //finds the = separating the variable name and value
        size_t equalsPos = line.find('=');

        //skips lines without =
        if (equalsPos == std::string::npos)
        {
            continue;
        }

        std::string key = line.substr(0, equalsPos);
        std::string value = line.substr(equalsPos + 1);

        //adds the variable to the environment
        setenv(key.c_str(), value.c_str(), 1);
    }
}

int main(int argc, char ** argv)
{
    loadEnv(".env");
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

    //gets player information from the clash royale api
    std::string playerData = client.getPlayer(argv[1]);

    //creates parser object
    PlayerParser playerParser;


    //converts JSON string into a Player object
    Player player = playerParser.parsePlayer(playerData);


    //prints player information
    std::cout << "My trophies: " << player.trophies << "\n";
    std::cout << "Best trophies: " << player.bestTrophies << "\n";
    
    //gets card information from the clash royale api
    std::string cardData = client.getCards();

    CardParser cardParser;

    std::vector<Card> cards =
    cardParser.parseCards(cardData);

    for (const auto& card : cards)
    {
    std::cout << card.name << " - " << card.elixirCost << " elixir\n";
    }

    //prints player,card json
    std::cout << "PLAYER JSON:\n";
    std::cout << playerData << "\n";
    std::cout << "CARD JSON:\n";
    std::cout << cardData << "\n";

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