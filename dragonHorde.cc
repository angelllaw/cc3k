#include "dragonHorde.h"
#include "human.h"
#include "elf.h"
#include "dwarf.h"
#include "orc.h"
#include <iostream>

// all the same function:

void DragonHorde::useOn(Human *p) {
    if (hasNoProtector()) p->addGold(gold);
}

void DragonHorde::useOn(Elf *p) {
    if (hasNoProtector()) p->addGold(gold);
}

void DragonHorde::useOn(Dwarf *p) {
    if (hasNoProtector()) p->addGold(gold * 2);
}

void DragonHorde::useOn(Orc *p) {
    if (hasNoProtector()) p->addGold(gold);
}

char DragonHorde::getChar() {
    return 'G';
}

bool DragonHorde::isGold() {
    return true;
}
