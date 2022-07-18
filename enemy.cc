#include "enemy.h"
#include <algorithm>
#include "info.h"

using namespace std;

// Enemy::~Enemy() {};

void Enemy::getAttacked(int damage) {
    int newHp = getInfo().hp - damage;
    setHp(max(0, newHp));
}
