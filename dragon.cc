#include "dragon.h"
#include "info.h"
#include "state.h"

using namespace std;

Dragon::Dragon() : baby{nullptr} {
    hasMoved = true;
    init(unique_ptr<Info> (new Info {150, 20, 20, 0}));
}

Dragon::~Dragon() {}

void Dragon::setDragonBaby(DragonBaby *baby) {
    this->baby = baby;
}

void Dragon::toggleMove() {}

char Dragon::getChar() { return 'D'; }

int Dragon::goldUponDead() {
    baby->setDragonMomma(nullptr);
    return stats->gold;
}

 bool Dragon::shouldAttack(State &myPos, State &otherPos) {
     // check if within vicinity of dragonBaby.
     // how do we know where dragonBaby is?
     // we can call something on DragonBaby...
     // probelm is finding the pos of dragonBaby 

    int xDist = myPos.x - otherPos.x;
    int yDist = myPos.y - otherPos.y;
    return (xDist*xDist <= 1 && yDist*yDist <= 1);
 }
