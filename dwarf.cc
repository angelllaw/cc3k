#include "dwarf.h"
#include "info.h"
#include "item.h"
#include <memory>

Dwarf::~Dwarf() {}

Dwarf::Dwarf() : Player(Race::Dwarf, Info{100, 20, 30, 0}) {}

void Dwarf::useItem(Item *i) {
    i->useOn(this);
}

