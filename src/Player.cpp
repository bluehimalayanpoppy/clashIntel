#include "Player.h"

//constructor
//runs automatically when a new Player object is created
//sets default values before the parser fills in json data
Player::Player()
{
    name = "";
    trophies = 0;
    bestTrophies = 0;

    currentDeck.clear();
}