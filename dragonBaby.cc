#include "dragonBaby.h"
#include "info.h"
#include "dragon.h"
#include <iostream>

// probably not necessary, this is a pure virtual class
DragonBaby::~DragonBaby() {}

bool DragonBaby::hasNoProtector() {
    return !hasProtector;
}

void DragonBaby::setProtector() {
    hasProtector = false;
}

bool DragonBaby::validUse() {
    if (hasProtector) std::cout << "You must slay the dragon protector first. " << std::endl;
    return !hasProtector;
}
