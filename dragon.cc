#include "dragon.h"
#include "info.h"
#include "state.h"
#include "dragonBaby.h"
#include <memory>
#include <iostream>

using namespace std;

Dragon::Dragon(DragonBaby *baby, State &babyPos) : baby{baby}, babyPos{babyPos} {
    stats = make_unique<Info>(Info{150, 20, 20, 0});
}

Dragon::~Dragon() {}

char Dragon::getChar() { return 'D'; }

int Dragon::goldUponDead() {
    baby->setProtector();
    return stats->gold;
}

State& Dragon::getBabyPos() {
    return babyPos;
}

 bool Dragon::shouldAttack(State &myPos, State &otherPos) {
    int xDist = babyPos.x - otherPos.x;
    int yDist = babyPos.y - otherPos.y;
    return (xDist*xDist <= 1 && yDist*yDist <= 1);
 }

bool Dragon::isStationary() {
    return true;
}
