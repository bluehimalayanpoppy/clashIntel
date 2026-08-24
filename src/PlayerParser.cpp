#include "PlayerParser.h"
#include <nlohmann/json.hpp>
#include <iostream>



using json = nlohmann::json;

//takes raw player JSON string from Clash API
//converts JSON data into a Player object
Player PlayerParser::parsePlayer(const std::string& jsonData)
{
    //converts raw string into a json object
    json parsedData = json::parse(jsonData);

    //checks if the API returned an error
    if (parsedData.contains("reason"))
    {
        std::cerr << "Player API error: " << parsedData["reason"].get<std::string>() << " - "  << parsedData["message"].get<std::string>()<< "\n";
        return Player();
    }

    //creates a new Player object
    //constructor gives it default values before api data is filled in
    Player player;
    //gets player's current trophy count
    player.trophies = parsedData["trophies"].get<int>();

    //gets player's highest trophy count
    player.bestTrophies = parsedData["bestTrophies"].get<int>();

    //returns completed Player object
    return player;
}