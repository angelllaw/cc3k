#include "dragonBaby.h"
#include "info.h"
#include "dragon.h"

// probably not necessary, this is a pure virtual class
DragonBaby::~DragonBaby() {}

void DragonBaby::setDragonMomma(Dragon *momma) {
    this->momma = momma;
    if (momma == nullptr) {
        deadDragon = true;
    } else {
        deadDragon = false;
    }
}

bool DragonBaby::isDragonDead() {
    return deadDragon;
}


bool DragonBaby::validUse() {
    return deadDragon;
}

