#include "dragon.h"
#include "info.h"

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
