#pragma once
#include <string>
#include <vector>

class Battle
{
public:

    //stores whether this battle was a win or loss
    bool won;
    //unique timestamp identifying this battle
    std::string battleTime;
    //player trophy information before/around the battle
    int myTrophies;
    int opponentTrophies;

    //number of crowns each player earned
    int myCrowns;
    int opponentCrowns;

    //cards used by each player
    //vector because the amount of cards can be stored dynamically
    std::vector<std::string> myDeck;
    std::vector<std::string> opponentDeck;

    //average level of cards in each deck
    //used later as numerical data for analysis
    double myAverageCardLevel;
    double opponentAverageCardLevel;


    //constructor
    //creates a battle object with default values
    Battle();

};