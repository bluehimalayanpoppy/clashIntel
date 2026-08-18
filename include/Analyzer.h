#pragma once

#include <vector>
#include "Battle.h"
#include "Card.h"

class Analyzer
{
public:

    //trains the analyzer using past battles
    void train(const std::vector<Battle>& battles, const std::vector<Card>& cards);

    //predicts the win probability for a battle
    double predict(const Battle& battle, const std::vector<Card>& cards) const;

private:

    //gets numerical features from a battle
    std::vector<double> getFeatures(
        const Battle& battle,
        const std::vector<Card>& cards) const;

    //converts a value into a probability
    double sigmoid(double x) const;

    //weights used by the model
    std::vector<double> weights;

    //bias used by the model
    double bias = 0.0;
};