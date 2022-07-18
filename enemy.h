#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character {
    
    void getAttacked(int damage) override;

    public:

    // ~Enemy(); // should be virtual, just for now
};

#endif
