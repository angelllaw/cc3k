#include "character.h"
#include "info.h"
#include "state.h"
#include <cmath>
#include <memory>

using namespace std;

Info &Character::getInfo() {
    return *stats;
}

void Character::setHp(int newHp) {
    stats->hp = newHp;
}
void Character::setAtk(int newAtk) {
    stats->atk = newAtk;
}
void Character::setDef(int newDef) {
    stats->def = newDef;
}
void Character::setGold(int newGold) {
    stats->gold = newGold;
}

bool Character::isDead() {
    return getInfo().hp == 0;
}

int Character::attack(Character &victim) {
    int damage = ceil((100.0 / (100 + victim.getInfo().def)) * getInfo().atk);
    damage = victim.getAttacked(damage);
    // enemies take damage normally
    // players have to check if they have barrier suit + 50% miss rate
    return damage;
}

Character::~Character() {}
