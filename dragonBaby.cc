#include "dragonBaby.h"
#include <iostream>

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
