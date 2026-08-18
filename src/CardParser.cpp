#include "CardParser.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;


//converts card json into Card objects
std::vector<Card> CardParser::parseCards(const std::string& jsonData)
{
    std::vector<Card> cards;

    //converts json string into json data
    json data = json::parse(jsonData);

    //goes through each card
    for (const auto& item : data["items"])
    {
        Card card;

        //gets basic card information
        card.name = item["name"];
        card.id = item["id"];
        card.maxLevel = item["maxLevel"];
        card.rarity = item["rarity"];

        //gets evolution level if it exists
        if (item.contains("maxEvolutionLevel"))
        {
            card.maxEvolutionLevel = item["maxEvolutionLevel"];
        }
        else
        {
            card.maxEvolutionLevel = 0;
        }

        //elixir cost if it exists
        if (item.contains("elixirCost"))
        {
            card.elixirCost = item["elixirCost"];
        }
        else
        {
            card.elixirCost = 0;
        }

        //adds card to the list
        cards.push_back(card);
    }

    return cards;
}