#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

class Player : public Character {
    State *pos;
    bool hasBarrierSuit = false;

    void getAttacked(int damage) override; 

    public:
        State &getState();
};

#endif
