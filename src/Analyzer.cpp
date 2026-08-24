#include "Analyzer.h"
#include <cmath>
#include <iostream>
#include <limits>

// Converts a score into a probability.
double Analyzer::sigmoid(double x) const
{
    // Prevent overflow in exp().
    if (x >= 0.0)
    {
        double z = std::exp(-x);
        return 1.0 / (1.0 + z);
    }
    else
    {
        double z = std::exp(x);
        return z / (1.0 + z);
    }
}

// Gets raw numerical features from a battle.
std::vector<double> Analyzer::getRawFeatures(
    const Battle& battle,
    const std::vector<Card>& cards) const
{
    double totalElixir = 0.0;

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

    double averageElixir = 0.0;

    if (!battle.myDeck.empty())
    {
        averageElixir =
            totalElixir / static_cast<double>(battle.myDeck.size());
    }

    return {
        static_cast<double>(battle.myTrophies),
        static_cast<double>(battle.opponentTrophies),
        battle.myAverageCardLevel,
        averageElixir
    };
}

// normalized features
std::vector<double> Analyzer::getFeatures(
    const Battle& battle,
    const std::vector<Card>& cards) const
{
    std::vector<double> features =
        getRawFeatures(battle, cards);

    for (size_t i = 0; i < features.size(); i++)
    {
        double range = featureMax[i] - featureMin[i];

        if (range != 0.0 && std::isfinite(range))
        {
            features[i] =
                (features[i] - featureMin[i]) / range;
        }
        else
        {
            features[i] = 0.0;
        }

        // Safety check.
        if (!std::isfinite(features[i]))
        {
            features[i] = 0.0;
        }
    }

    return features;
}

// Trains the analyzer.
void Analyzer::train(
    const std::vector<Battle>& battles,
    const std::vector<Card>& cards)
{
    if (battles.empty())
    {
        return;
    }

    weights = std::vector<double>(4, 0.0);
    bias = 0.0;

    featureMin =
        getRawFeatures(battles[0], cards);

    featureMax =
        featureMin;

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

    for (int epoch = 0; epoch < epochs; epoch++)
    {
        std::vector<double> weightGradient(4, 0.0);
        double biasGradient = 0.0;

        for (const auto& battle : battles)
        {
            std::vector<double> features =
                getFeatures(battle, cards);

            double score = bias;

            for (size_t i = 0; i < features.size(); i++)
            {
                score += weights[i] * features[i];
            }

            // Safety check for invalid scores.
            if (!std::isfinite(score))
            {
                std::cerr
                    << "ERROR: Invalid analyzer score during training\n";

                return;
            }

            double prediction = sigmoid(score);

            double actual = battle.won ? 1.0 : 0.0;

            double error =prediction - actual;

            for (size_t i = 0; i < features.size(); i++)
            {
                weightGradient[i] += error * features[i];
            }

            biasGradient += error;
        }

        for (size_t i = 0; i < weights.size(); i++)
        {
            weights[i] -=learningRate *(weightGradient[i] /static_cast<double>(battles.size()));
        }

        bias -=learningRate *(biasGradient /static_cast<double>(battles.size()));
    }
}

// Predicts win probability.
double Analyzer::predict(const Battle& battle,const std::vector<Card>& cards) const
{
    if (weights.empty())
    {
        return 0.5;
    }

    std::vector<double> features =getFeatures(battle, cards);

    double score = bias;

    for (size_t i = 0; i < features.size(); i++)
    {
        score += weights[i] * features[i];
    }


    // never allow NaN/Infinity to reach the GUI.
    if (!std::isfinite(score))
    {
        std::cerr
            << "ERROR: Analyzer produced invalid score\n";

        return 0.5;
    }

    double probability = sigmoid(score);

    if (!std::isfinite(probability))
    {
        std::cerr
            << "ERROR: Analyzer produced invalid probability\n";

        return 0.5;
    }

    return probability;
}

// calculates historical win rate
double Analyzer::getWinRate(const std::vector<Battle>& battles) const
{
    if (battles.empty())
    {
        return 0.0;
    }

    int wins = 0;

    for (const auto& battle : battles)
    {
        if (battle.won)
        {
            wins++;
        }
    }

    return static_cast<double>(wins) /static_cast<double>(battles.size());
}