#include "elf.h"
#include "info.h"
#include "item.h"
#include <memory>

Elf::~Elf() {}

Elf::Elf() : Player(Race::Elf, Info{140, 30, 10, 0}) {}

void Elf::useItem(Item *i) {
    i->useOn(this);
}
