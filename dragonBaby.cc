#include "dragonBaby.h"
#include "info.h"
#include "dragon.h"

// probably not necessary, this is a pure virtual class
DragonBaby::~DragonBaby() {}

/*
void DragonBaby::setDragonMomma(Dragon *momma) {
    this->momma = momma;
    if (momma == nullptr) {
        hasProtector = true;
    } else {
        hasProtector = false;
    }
}
*/

bool DragonBaby::isDragonDead() {
    return hasProtector;
}

void DragonBaby::setDeadMom() {
    hasProtector = false;
}


bool DragonBaby::validUse() {
    return hasProtector;
}

