#include "orc.h"
#include "info.h"
#include "item.h"
#include <memory>

Orc::~Orc() {}

Orc::Orc() : Player(Race::Orc, Info{180, 30, 25, 0}) {}

void Orc::useItem(Item *i) {
    i->useOn(this);
}
