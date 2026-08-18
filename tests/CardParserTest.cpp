#include <iostream>
#include <string>
#include "CardParser.h"

int main()
{
    //creates parser object
    CardParser parser;

    //example response from the /cards endpoint
    std::string cardData = R"({
        "items": [
            {
                "name": "Knight",
                "id": 26000000,
                "maxLevel": 16,
                "maxEvolutionLevel": 1,
                "elixirCost": 3,
                "iconUrls": {
                    "medium": "test.png"
                },
                "rarity": "common"
            }
        ],
        "supportItems": []
    })";

    //converts json string into card objects
    std::vector<Card> cards = parser.parseCards(cardData);

    //prints parsed card information
    for (const auto& card : cards)
    {
        std::cout << "Name: " << card.name << "\n";
        std::cout << "ID: " << card.id << "\n";
        std::cout << "Max level: " << card.maxLevel << "\n";
        std::cout << "Max evolution level: " << card.maxEvolutionLevel << "\n";
        std::cout << "Elixir cost: " << card.elixirCost << "\n";
        std::cout << "Rarity: " << card.rarity << "\n";
        std::cout << "---------------------\n";
    }

    return 0;
}