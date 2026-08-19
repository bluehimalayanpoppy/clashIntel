#include <iostream>
#include <fstream>
#include <cstdlib>

#include "ClashClient.h"
#include "BattleParser.h"
#include "CardParser.h"
#include "Analyzer.h"

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

int main(int argc, char** argv)
{
    loadEnv(".env");

    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0]  << " <player_tag>\n";
        return 1;
    }

    //gets api token from environment variable
    const char* token =
        std::getenv("CLASH_API_TOKEN");

    if (!token)
    {
        std::cerr << "Error: set CLASH_API_TOKEN environment variable\n";
        return 1;
    }

    //creates api client
    ClashClient client(token);

    //gets battle and card data from the api
    std::string battleData = client.getBattleLog(argv[1]);

    std::string cardData =client.getCards();

    //creates parser objects
    BattleParser battleParser;
    CardParser cardParser;

    //converts json data into objects
    std::vector<Battle> battles = battleParser.parseBattles(battleData);

    std::vector<Card> cards = cardParser.parseCards(cardData);

    //checks that data was actually loaded
    std::cout << "Battles loaded: " << battles.size() << "\n";

    std::cout << "Cards loaded: " << cards.size() << "\n";

    if (battles.empty())
    {
        std::cerr << "Error: no battles found\n";
        return 1;
    }

    //creates the analyzer
    Analyzer analyzer;

    //trains the analyzer using past battles
    analyzer.train(battles, cards);

    //uses one of the battles to test the prediction
    double probability = analyzer.predict(battles[0], cards);

    //prints the predicted win probability
    std::cout << "Predicted win probability: " << probability * 100.0 << "%\n";
    return 0;
}