#include "BattleParser.h"

#include <nlohmann/json.hpp>
#include <iostream>


//short name for nlohmann json library
//allows us to write json instead of nlohmann::json every time
using json = nlohmann::json;

//takes raw json string from Clash API
//converts json data into Battle objects
std::vector<Battle> BattleParser::parseBattles(const std::string& jsonData)
{
    //stores all battles after they are converted into Battle objects
    std::vector<Battle> battles;

    //converts raw string from API into a json object
    //allows us to access fields like team, opponent, crowns, cards, etc.
    json parsedData = json::parse(jsonData);

    //loops through every battle inside the API response
    //each item inside parsedData represents one battle
    for (const auto& battleData : parsedData)
    {
        //some entries in the battle log may not be normal battles
        //skip anything that is not a JSON object
        if (!battleData.is_object())
        {
            continue;
        }

        //creates a new Battle object
        //constructor gives it default values before we fill in API data
        Battle battle;

        //gets the unique timestamp for this battle
        if (battleData.contains("battleTime") &&
            battleData["battleTime"].is_string())
        {
            battle.battleTime =
                battleData["battleTime"].get<std::string>();
        }

        //make sure the battle contains both team and opponent
        if (!battleData.contains("team") ||
            !battleData["team"].is_array() ||
            battleData["team"].empty())
        {
            continue;
        }

        if (!battleData.contains("opponent") ||
            !battleData["opponent"].is_array() ||
            battleData["opponent"].empty())
        {
            continue;
        }

        //team is an array
        //team[0] is our player because this is the player's battle log
        const auto& myPlayer = battleData["team"][0];


        //opponent is also an array
        //opponent[0] contains the enemy player data
        const auto& enemyPlayer = battleData["opponent"][0];

        //make sure both player entries are objects
        if (!myPlayer.is_object() || !enemyPlayer.is_object())
        {
            continue;
        }



        //gets trophy count before the battle started
        if (myPlayer.contains("startingTrophies") &&
            myPlayer["startingTrophies"].is_number())
        {
            battle.myTrophies =
                myPlayer["startingTrophies"].get<int>();
        }

        if (enemyPlayer.contains("startingTrophies") &&
            enemyPlayer["startingTrophies"].is_number())
        {
            battle.opponentTrophies =
                enemyPlayer["startingTrophies"].get<int>();
        }



        //gets the number of crowns earned by each player
        if (myPlayer.contains("crowns") &&
            myPlayer["crowns"].is_number())
        {
            battle.myCrowns =
                myPlayer["crowns"].get<int>();
        }

        if (enemyPlayer.contains("crowns") &&
            enemyPlayer["crowns"].is_number())
        {
            battle.opponentCrowns =
                enemyPlayer["crowns"].get<int>();
        }




        //checks who won the battle
        //more crowns means the player won
        if (battle.myCrowns > battle.opponentCrowns)
        {
            battle.won = true;
        }
        else
        {
            battle.won = false;
        }

        //temporary variable to add up all card levels
        //used later to calculate average card level
        int myTotalCardLevels = 0;

        //loops through every card in our deck
        if (myPlayer.contains("cards") &&
            myPlayer["cards"].is_array())
        {
            for (const auto& card : myPlayer["cards"])
            {
                //make sure this is actually a card object
                if (!card.is_object())
                {
                    continue;
                }

                //gets the card name from JSON
                if (card.contains("name") &&
                    card["name"].is_string())
                {
                    std::string cardName =
                        card["name"].get<std::string>();


                    //adds card name to our deck vector
                    battle.myDeck.push_back(cardName);
                }


                //adds card level to total
                if (card.contains("level") &&
                    card["level"].is_number())
                {
                    myTotalCardLevels +=
                        card["level"].get<int>();
                }
            }
        }


        //calculates average card level
        //only runs if there are cards inside the deck
        if (!battle.myDeck.empty())
        {
            battle.myAverageCardLevel =
                (double)myTotalCardLevels /
                battle.myDeck.size();
        }



        //same process for opponent cards
        int opponentTotalCardLevels = 0;

        if (enemyPlayer.contains("cards") &&
            enemyPlayer["cards"].is_array())
        {
            for (const auto& card : enemyPlayer["cards"])
            {
                //make sure this is actually a card object
                if (!card.is_object())
                {
                    continue;
                }

                //gets opponent card name
                if (card.contains("name") &&
                    card["name"].is_string())
                {
                    std::string cardName =
                        card["name"].get<std::string>();


                    //adds card to opponent deck
                    battle.opponentDeck.push_back(cardName);
                }


                //adds card level to total
                if (card.contains("level") &&
                    card["level"].is_number())
                {
                    opponentTotalCardLevels +=
                        card["level"].get<int>();
                }
            }
        }


        //calculates opponent average card level
        if (!battle.opponentDeck.empty())
        {
            battle.opponentAverageCardLevel =
                (double)opponentTotalCardLevels /
                battle.opponentDeck.size();
        }
        //after all JSON data has been copied into the Battle object
        //store the completed battle inside the vector
        battles.push_back(battle);

    }


    //returns all converted battles
    return battles;
}