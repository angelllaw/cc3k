#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character {
    char e = 'e'; // DELETE
    public:

    ~Enemy(); // should be virtual, just for now
};

#endif
