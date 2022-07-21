#include "dragonHorde.h"
#include "human.h"
#include "elf.h"
#include "dwarf.h"
#include "orc.h"

// all the same function:

void DragonHorde::useOn(Human *p) {
    p->addGold(gold);
}

void DragonHorde::useOn(Elf *p) {
    p->addGold(gold);
}

void DragonHorde::useOn(Dwarf *p) {
    p->addGold(gold);
}

void DragonHorde::useOn(Orc *p) {
    p->addGold(gold);
}
