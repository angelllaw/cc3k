#include "player.h"
#include <algorithm>
#include "random.h"
#include "info.h"
#include "state.h"
using namespace std;

Player::~Player() {}

Player::Player(Race race, Info stats) : atk{stats.atk}, def{stats.def}, race{race} {
    this->stats = make_unique<Info>(Info{140, 20, 20, 0});
}

void Player::getAttacked(int damage) {
    Random r;
    if (hasBarrierSuit) damage /= 2;
    int newHp = getInfo().hp - damage;
    // 50% chance player takes damage
    if (r.randomNum(2) == 1) setHp(max(0, newHp));
} 

State &Player::getState() {
    return *pos;
}

void Player::setState(State newPos) {
    *pos = newPos;
} 

Race Player::getRace() {
    return race;
}

