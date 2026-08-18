#include "Analyzer.h"
#include <cmath>

//converts a value into a probability
double Analyzer::sigmoid(double x) const
{
    return 1.0 / (1.0 + std::exp(-x));
}

//gets numerical features from a battle
std::vector<double> Analyzer::getFeatures(
    const Battle& battle,
    const std::vector<Card>& cards) const
{
    double totalElixir = 0.0;

    //finds the elixir cost of each card in the deck
    for (const auto& cardName : battle.myDeck)
    {
        for (const auto& card : cards)
        {
            if (card.name == cardName)
            {
                totalElixir += card.elixirCost;
                break;
            }
        }
    }

    //calculates average elixir for the deck
    double averageElixir = 0.0;

    if (!battle.myDeck.empty())
    {
        averageElixir = totalElixir / battle.myDeck.size();
    }

    //returns all features as a vector
    return {
        static_cast<double>(battle.myTrophies),
        static_cast<double>(battle.opponentTrophies),
        battle.myAverageCardLevel,
        averageElixir
    };
}

//trains the analyzer using past battles
void Analyzer::train(const std::vector<Battle>& battles,const std::vector<Card>& cards)
{
}

//predicts the win probability for a battle
double Analyzer::predict(
    const Battle& battle,
    const std::vector<Card>& cards) const
{
    std::vector<double> features =
        getFeatures(battle, cards);

    return 0.5;
}