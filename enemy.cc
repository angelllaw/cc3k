#include "enemy.h"
#include <algorithm>
#include <iostream>
#include "info.h"
#include "state.h"

using namespace std;

// Enemy::~Enemy() {};

int Enemy::getAttacked(int damage) {
    int oldHp = getInfo().hp;
    int newHp = oldHp - damage;
    setHp(max(0, newHp));
    return min(damage, oldHp);
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

bool Enemy::shouldAttack(State &myPos, State &otherPos) {
    int xDist = myPos.x - otherPos.x;
    int yDist = myPos.y - otherPos.y;
    return (xDist*xDist <= 1 && yDist*yDist <= 1);
}
