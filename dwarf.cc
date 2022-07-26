#include "dwarf.h"
#include "info.h"
#include "item.h"
#include "state.h"

#include <memory>

using namespace std;

Dwarf::~Dwarf() {}

Dwarf::Dwarf() : Player{100, 20, 30} {
    stats = make_unique<Info>(Info{100, 20, 30, 0});
}

void Dwarf::useItem(Item *i) {
    i->useOn(this);
    setHp(min(defaultStats->hp, stats->hp));
}

string Dwarf::printRace() {
    return "Dwarf";
}
