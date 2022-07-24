#include "dragonHorde.h"
#include "human.h"
#include "elf.h"
#include "dwarf.h"
#include "orc.h"
#include <iostream>

// all the same function:

void DragonHorde::useOn(Human *p) {
    if (isDragonDead()) {
        p->addGold(gold);
    } else {
        std::cout << "The Dragon is still guarding the treasure. You must kill the Dragon first." << std::endl;
    }
}

void DragonHorde::useOn(Elf *p) {
    if (isDragonDead()) {
        p->addGold(gold);
    } else {
        std::cout << "The Dragon is still guarding the treasure. You must kill the Dragon first." << std::endl;
    }
}

void DragonHorde::useOn(Dwarf *p) {
    if (isDragonDead()) {
        p->addGold(gold);
    } else {
        std::cout << "The Dragon is still guarding the treasure. You must kill the Dragon first." << std::endl;
    }
}

void DragonHorde::useOn(Orc *p) {
    if (isDragonDead()) {
        p->addGold(gold);
    } else {
        std::cout << "The Dragon is still guarding the treasure. You must kill the Dragon first." << std::endl;
    }
}

char DragonHorde::getChar() {
    return 'G';
}

bool DragonHorde::isGold() {
    return true;
}

