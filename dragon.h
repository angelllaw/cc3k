#ifndef DRAGON_H
#define DRAGON_H

#include <memory>
#include "enemy.h"
#include "state.h"

class DragonBaby;

class Dragon : public Enemy {
    // still need to implement pointer to DragonBaby

    DragonBaby *baby; // don't destroy this when dragon dies since tile still owns it

    public:
    Dragon(DragonBaby *baby);
    ~Dragon();
    bool shouldAttack(State &myPos, State &otherPos) override;
    void toggleMove() override;
    // void setDragonBaby(DragonBaby *baby);
    char getChar() override;
    int goldUponDead() override;
};

#endif
