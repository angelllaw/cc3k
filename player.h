#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

class Player : public Character {
    const int atk = 20; // human default
    const int def = 20; // human defualt
    State *pos;
    bool hasBarrierSuit = false;

    void getAttacked(int damage) override; 

    public:
        State &getState();
        void setState(State newPos);
        ~Player();
};

#endif
