#include "barrierSuit.h"
#include "human.h"
/* #include "elf.h"
#include "dwarf.h"
#include "orc.h" */

void BarrierSuit::useOn(Human *p) {
    p->setBarrierSuitTrue();
}

/* void BarrierSuit::useOn(Elf *p) {
    p->setBarrierSuitTrue();
}

void BarrierSuit::useOn(Dwarf *p) {
    p->setBarrierSuitTrue();
}

void BarrierSuit::useOn(Orc *p) {
    p->setBarrierSuitTrue();
} */
