#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

#include <QApplication>

#include "ClashClient.h"
#include "BattleParser.h"
#include "CsvExporter.h"
#include "PlayerParser.h"
#include "CardParser.h"
#include "Analyzer.h"
#include "CsvReader.h"
#include "MainWindow.h"

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

        std::string key =
            line.substr(0, equalsPos);

        std::string value =
            line.substr(equalsPos + 1);

        //adds the variable to the environment
        setenv(key.c_str(), value.c_str(), 1);
    }
}

int main(int argc, char **argv)
{
    loadEnv(".env");

    if (argc < 2)
    {
        std::cerr << "Usage: "<< argv[0] << " <player_tag>\n";

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

    std::cout << "Fetching player data...\n";

    std::string playerData = client.getPlayer(argv[1]);

    PlayerParser playerParser;

    Player player = playerParser.parsePlayer(playerData);

    std::cout << "Trophies: " << player.trophies << "\n";

    std::cout << "Best trophies: " << player.bestTrophies << "\n";

    std::cout << "Fetching card data...\n";

    std::string cardData = client.getCards();

    CardParser cardParser;

    std::vector<Card> cards = cardParser.parseCards(cardData);

    std::cout << "Cards loaded: " << cards.size() << "\n";

    std::cout << "Fetching battle log...\n";

    std::string battleData = client.getBattleLog(argv[1]);

    BattleParser parser;

    std::vector<Battle> battles = parser.parseBattles(battleData);

    std::cout << "Current battles loaded: "<< battles.size() << "\n";

    if (battles.empty())
    {
        std::cerr<< "ERROR: No current battles were parsed.\n";

        return 1;
    }

    std::cout << "Loading historical battles...\n";

    std::vector<Battle> savedBattles =CsvReader::readBattles("data/battles.csv");

    std::cout << "Historical battles: "<< savedBattles.size()<< "\n";

    //trains analyzer using historical data
    std::cout << "Training analyzer...\n";

    Analyzer analyzer;

    analyzer.train(savedBattles,cards);

    std::cout << "Analyzer trained successfully.\n";

    //predicts the first current battle
    double prediction =analyzer.predict(battles[0],cards);

    double historicalWinRate =analyzer.getWinRate(savedBattles);

    bool predictedWin = prediction >= 0.5;

    //exports the current battles
    if (CsvExporter::exportBattles(
            battles,
            "data/battles.csv"))
    {
        std::cout
            << "Battles exported successfully.\n";
    }

    //creates the Qt application
    QApplication app(argc, argv);

    MainWindow window(
        prediction,
        historicalWinRate,
        battles[0].myTrophies,
        battles[0].opponentTrophies,
        battles[0].myAverageCardLevel,
        predictedWin
    );

    window.show();

    return app.exec();
}