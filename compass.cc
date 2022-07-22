#include "compass.h"
#include "human.h"
#include "elf.h"
#include "dwarf.h"
#include "orc.h"

#include <iostream>

void Compass::useOn(Human *p) {
    p->setCompassTrue();
}

void Compass::useOn(Elf *p) {
    p->setCompassTrue();
}

void Compass::useOn(Dwarf *p) {
    p->setCompassTrue();
}

void Compass::useOn(Orc *p) {
    p->setCompassTrue();
}

char Compass::getChar() {
    return 'C';
}

Compass::~Compass() {}
