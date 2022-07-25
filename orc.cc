#include "orc.h"
#include "info.h"
#include "item.h"
#include "state.h"
#include <memory>

using namespace std;

Orc::~Orc() {}

Orc::Orc() : Player{180, 30, 25} {
    stats = make_unique<Info>(Info{180, 30, 25, 0});
}

void Orc::useItem(Item *i) {
    i->useOn(this);
}

string Orc::printRace() {
    return "Orc";
}
