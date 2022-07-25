#ifndef DRAGON_H
#define DRAGON_H

#include <memory>
#include "enemy.h"
#include "state.h"

class DragonBaby;

class Dragon : public Enemy {

    DragonBaby *baby;
    State babyPos;
    State& getBabyPos();

    public:
    Dragon(DragonBaby *baby, State &babyPos);
    ~Dragon();
    bool shouldAttack(State &myPos, State &otherPos) override;
    char getChar() override;
    int goldUponDead() override;
    bool isStationary() override;
};

#endif
