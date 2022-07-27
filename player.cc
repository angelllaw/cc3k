#include "player.h"
#include <algorithm>
#include <cmath>
#include "info.h"
#include "state.h"
#include "direction.h"
using namespace std;

Player::~Player() {}

Player::Player(int hp, int atk, int def) : defaultStats{make_unique<const Info>(Info{hp, atk, def, 0})}, pos{make_unique<State>()} {}

int Player::getAttacked(int damage) {
    if (hasBarrierSuit) damage /= 2;
    int oldHp = getInfo().hp;
    int newHp = getInfo().hp - damage;
    setHp(max(0, newHp));
    return min(damage, oldHp);
} 

State &Player::getState() {
    return *pos;
}

void Player::setState(State newPos) {
    pos->x = newPos.x;
    pos->y = newPos.y;
} 

void Player::setBarrierSuitTrue() {
    hasBarrierSuit = true;
}

void Player::setCompassTrue() {
    compass = true;
}

bool Player::hasCompass() {
    return compass;
}

void Player::addGold(int amount) {
    stats->gold = stats->gold + amount;
}

void Player::move(Direction dir) {
    int curX = this->getState().x;
    int curY = this->getState().y;
    int newX = curX;
    int newY = curY;

    switch(dir) {
        case Direction::N:
            newY -= 1;
            break;
        case Direction::NE:
            newX += 1;
            newY -= 1;
            break;
        case Direction::E:
            newX += 1;
            break;
        case Direction::SE:
            newX += 1;
            newY += 1;
            break;
        case Direction::S:
            newY += 1;
            break;
        case Direction::SW:
            newX -= 1;
            newY += 1;
            break;
        case Direction::W:
            newX -= 1;
            break;
        case Direction::NW:
            newX -= 1;
            newY -= 1;
            break;
    }
    setState(State {newX, newY});
}

void Player::reset() {
    // reset atk and def
    stats->atk = defaultStats->atk;
    stats->def = defaultStats->def;
    // reset compass
    compass = false;
}

int Player::getScore() {
    return stats->gold;
}
