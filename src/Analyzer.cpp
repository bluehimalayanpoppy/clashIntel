#include "Analyzer.h"
#include <cmath>

//converts the weighted feature score into a probability
double Analyzer::sigmoid(double x) const
{
    return 1.0 / (1.0 + std::exp(-x));
}

//gets the raw numerical features from a battle
std::vector<double> Analyzer::getRawFeatures(
    const Battle& battle,
    const std::vector<Card>& cards) const
{
    double totalElixir = 0.0;

    //finds the elixir cost of each card in the player's deck
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

    //calculates the average elixir cost of the player's deck
    double averageElixir = 0.0;

    if (!battle.myDeck.empty())
    {
        averageElixir = totalElixir / battle.myDeck.size();
    }

    //returns the raw numerical features used by the analyzer
    return {
        static_cast<double>(battle.myTrophies),
        static_cast<double>(battle.opponentTrophies),
        battle.myAverageCardLevel,
        averageElixir
    };
}

//gets normalized numerical features from a battle
std::vector<double> Analyzer::getFeatures(
    const Battle& battle,
    const std::vector<Card>& cards) const
{
    //gets the raw values before normalization
    std::vector<double> features = getRawFeatures(battle, cards);

    //normalizes each feature using the values found during training
    for (size_t i = 0; i < features.size(); i++)
    {
        double range = featureMax[i] - featureMin[i];

        if (range != 0.0)
        {
            features[i] = (features[i] - featureMin[i]) / range;
        }
        else
        {
            features[i] = 0.0;
        }
    }

    return features;
}

//trains the analyzer by adjusting feature weights using gradient descent
void Analyzer::train(
    const std::vector<Battle>& battles,
    const std::vector<Card>& cards)
{
    if (battles.empty())
    {
        return;
    }

    //start with one weight for each feature
    weights = std::vector<double>(4, 0.0);
    bias = 0.0;

    //start the minimum and maximum values using the first battle
    featureMin = getRawFeatures(battles[0], cards);

    featureMax = featureMin;

    //find the minimum and maximum value for each feature
    for (const auto& battle : battles)
    {
        std::vector<double> features =
            getRawFeatures(battle, cards);

        for (size_t i = 0; i < features.size(); i++)
        {
            if (features[i] < featureMin[i])
            {
                featureMin[i] = features[i];
            }

            if (features[i] > featureMax[i])
            {
                featureMax[i] = features[i];
            }
        }
    }

    double learningRate = 0.01;
    int epochs = 1000;

    //repeatedly adjust the weights using past battle results
    for (int epoch = 0; epoch < epochs; epoch++)
    {
        std::vector<double> weightGradient(4, 0.0);
        double biasGradient = 0.0;

        for (const auto& battle : battles)
        {
            std::vector<double> features = getFeatures(battle, cards);

            //calculate the weighted score
            double score = bias;

            for (size_t i = 0; i < features.size(); i++)
            {
                score += weights[i] * features[i];
            }

            //convert the score into a win probability
            double prediction = sigmoid(score);

            //1 for a win, 0 for a loss
            double actual = battle.won ? 1.0 : 0.0;

            //calculate how far the prediction was from the result
            double error = prediction - actual;

            //calculate the gradient for each feature
            for (size_t i = 0; i < features.size(); i++)
            {
                weightGradient[i] += error * features[i];
            }

            biasGradient += error;
        }

        //update the weights in the direction that reduces the error
        for (size_t i = 0; i < weights.size(); i++)
        {
            weights[i] -= learningRate * (weightGradient[i] / battles.size());
        }

        //update the bias
        bias -= learningRate *
                (biasGradient / battles.size());
    }
}

//predicts the win probability for a battle
double Analyzer::predict(
    const Battle& battle,
    const std::vector<Card>& cards) const
{
    if (weights.empty())
    {
        return 0.5;
    }

    std::vector<double> features =
        getFeatures(battle, cards);

    //multiply each feature by its learned weight
    double score = bias;

    //score is bias + w1 * trophies, w2 * opponent trophies, etc.
    for (size_t i = 0; i < features.size(); i++)
    {
        score += weights[i] * features[i];
    }

    //convert the final score into a probability
    //1 / (1 + exp(-x))
    return sigmoid(score);
}