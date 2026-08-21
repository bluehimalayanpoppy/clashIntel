#pragma once

#include <vector>
#include "Battle.h"
#include "Card.h"

class Analyzer
{
private:

    //weights learned from past battles
    std::vector<double> weights;

    //bias learned during training
    double bias;

    //minimum and maximum values used to normalize each feature
    std::vector<double> featureMin;
    std::vector<double> featureMax;

    //converts the weighted feature score into a probability
    double sigmoid(double x) const;

    //gets the raw numerical features from a battle
    std::vector<double> getRawFeatures(const Battle& battle,const std::vector<Card>& cards) const;

    //gets normalized numerical features from a battle
    std::vector<double> getFeatures(const Battle& battle,const std::vector<Card>& cards) const;

public:

    //trains the analyzer using past battles
    void train(const std::vector<Battle>& battles,  const std::vector<Card>& cards);

    //predicts the win probability for a battle
    double predict(const Battle& battle,const std::vector<Card>& cards) const;
    //the actual win rate from the training battles
    double getWinRate(const std::vector<Battle>& battles) const;
};