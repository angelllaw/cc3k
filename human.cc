#include "human.h"
#include "info.h"
#include "item.h"
#include "state.h"
#include <memory>
#include <iostream>

using namespace std;

Human::Human() : Player{140, 20, 20} {
    stats = make_unique<Info>(Info{140, 20, 20, 0});
}

Human::~Human() {}

void Human::useItem(Item *i) {
    i->useOn(this);

}

string Human::printRace() {
    return "Human";
}

int Human::getScore() {
    return stats->gold * 1.5;
}

