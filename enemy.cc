#include "enemy.h"
#include <algorithm>
#include <iostream>
#include "info.h"

using namespace std;

// Enemy::~Enemy() {};

void Enemy::getAttacked(int damage) {
    int newHp = getInfo().hp - damage;
    setHp(max(0, newHp));
}

Enemy::~Enemy() {}

std::ostream &operator<<(std::ostream &out, const Enemy &e) {
    switch (e.id) {
        case EnemyType::Werewolf:
            out << 'W';
            break;
        case EnemyType::Vampire:
            out << 'V';
            break;
        case EnemyType::Goblin:
            out << 'N';
            break;
        case EnemyType::Troll:
            out << 'T';
            break;
        case EnemyType::Phoenix:
            out << 'X';
            break;
        case EnemyType::Merchant:
            out << 'M';
            break;
        default: // Dragon
            out << 'D';
            break;
    }
    return out;
}
