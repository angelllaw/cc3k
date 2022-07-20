#include "human.h"
#include "info.h"
#include "item.h"
#include <memory>

Human::Human() : Player(Race::Human, Info{140, 20, 20, 0}) {}

Human::~Human() {}

void Human::useItem(Item *i) {
    i->useOn(this);
}

