#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

class Player : public Character {

    bool hasBarrierSuit = false;

    void getAttacked(int damage) override; 
};

#endif
