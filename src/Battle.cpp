#include "Battle.h"



//constructor
//runs automatically when a new object is created, will set default values before the parser fills in JSON data
Battle::Battle()
{
    won = false;
    myTrophies = 0;
    opponentTrophies = 0;

    myCrowns = 0;
    opponentCrowns = 0;

    myAverageCardLevel = 0.0;
    opponentAverageCardLevel = 0.0;

    myDeck.clear();
    opponentDeck.clear();

    //cards will be added later when parsing JSON
}