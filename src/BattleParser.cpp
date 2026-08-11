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

        //creates a new Battle object
        //constructor gives it default values before we fill in API data
        Battle battle;



        //team is an array
        //team[0] is our player because this is the player's battle log
        auto myPlayer = battleData["team"][0];


        //opponent is also an array
        //opponent[0] contains the enemy player data
        auto enemyPlayer = battleData["opponent"][0];



        //gets trophy count before the battle started
        battle.myTrophies = myPlayer["startingTrophies"];

        battle.opponentTrophies = enemyPlayer["startingTrophies"];



        //gets the number of crowns earned by each player
        battle.myCrowns = myPlayer["crowns"];

        battle.opponentCrowns = enemyPlayer["crowns"];



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
        for (const auto& card : myPlayer["cards"])
        {

            //gets the card name from JSON
            std::string cardName = card["name"];


            //adds card name to our deck vector
            battle.myDeck.push_back(cardName);



            //adds card level to total
            myTotalCardLevels += card["level"].get<int>(); 

        }

        //calculates average card level
        //only runs if there are cards inside the deck
        if (!battle.myDeck.empty())
        {
            battle.myAverageCardLevel =
                (double)myTotalCardLevels / battle.myDeck.size();
        }

        //same process for opponent cards
        int opponentTotalCardLevels = 0;

        for (const auto& card : enemyPlayer["cards"])
        {

            //gets opponent card name
            std::string cardName = card["name"];


            //adds card to opponent deck
            battle.opponentDeck.push_back(cardName);


            //adds card level to total //convert to int so it isn't json + int 
            opponentTotalCardLevels += card["level"].get<int>();

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