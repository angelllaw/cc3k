#include "enemy.h"
#include <algorithm>
#include <iostream>
#include "info.h"
#include "state.h"
#include "compass.h"

using namespace std;

// Enemy::~Enemy() {};

int Enemy::getAttacked(int damage) {
    int oldHp = getInfo().hp;
    int newHp = oldHp - damage;
    setHp(max(0, newHp));
    return min(damage, oldHp);
}

void Enemy::toggleMove() {
    hasMoved = !hasMoved;
}

Enemy::~Enemy() {}

bool Enemy::shouldAttack(State &myPos, State &otherPos) {
    int xDist = myPos.x - otherPos.x;
    int yDist = myPos.y - otherPos.y;
    return (xDist*xDist <= 1 && yDist*yDist <= 1);
}

bool Enemy::hasCompass() {
    if (c.get() == nullptr) return false;
    return true;
}

void Enemy::setCompass(unique_ptr<Compass> &c) {
    this->c = std::move(c);
}

std::unique_ptr<Compass>& Enemy::getCompass() {
    return c; // bruh i got no idea if this is valid
}