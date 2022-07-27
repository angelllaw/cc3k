#include "elf.h"
#include "info.h"
#include "item.h"
#include <memory>

using namespace std;

Elf::~Elf() {}

Elf::Elf() : Player{140, 30, 10} {
    stats = make_unique<Info>(Info{140, 30, 10, 0});
}

void Elf::useItem(Item *i) {
    i->useOn(this);
    setHp(min(defaultStats->hp, stats->hp));
}

string Elf::printRace() {
    return "Elf";
}
