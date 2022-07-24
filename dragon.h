#ifndef DRAGON_H
#define DRAGON_H

#include "dragonBaby.h"
#include "enemy.h"

class Dragon : public Enemy {
    // still need to implement pointer to DragonBaby
    DragonBaby *baby;

    public:
    Dragon();
    ~Dragon();
    bool shouldAttack(State &myPos, State &otherPos) override;
    void toggleMove() override;
    void setDragonBaby(DragonBaby *baby);
    char getChar() override;
    int goldUponDead() override;
};

#endif
