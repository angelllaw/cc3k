#include "dragonHorde.h"
#include "human.h"
/* #include "elf.h"
#include "dwarf.h"
#include "orc.h" */

void DragonHorde::useOn(Human *p) {
    p->addGold(gold);
}

/* void DragonHorde::useOn(Elf *p) {
    p->addGold(gold);
}

void DragonHorde::useOn(Dwarf *p) {
    p->addGold(gold);
}

void DragonHorde::useOn(Orc *p) {
    p->addGold(gold);
}
 */