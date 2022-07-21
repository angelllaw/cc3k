#include "player.h"
#include <algorithm>
#include <iostream>
#include "random.h"
#include "info.h"
#include "state.h"
#include "direction.h"
using namespace std;

Player::~Player() {}

Player::Player(const int atk, const int def) : atk{atk}, def{def}, pos{make_unique<State>()} {}

/*
Player::Player(Race race, Info stats) : atk{stats.atk}, def{stats.def}, race{race}, pos{make_unique<State>()} {
    this->stats = make_unique<Info>(Info{140, 20, 20, 0});
    pos->x = 0;
    pos->y = 0;
}
*/
void Player::getAttacked(int damage) {
    cout << "Player is attacked, damage: " << damage << endl;
    Random r;
    if (hasBarrierSuit) damage /= 2;
    int newHp = getInfo().hp - damage;
    // 50% chance player takes damage
    if (r.randomNum(2) == 0) {
        setHp(max(0, newHp));
        cout << "attack lands on player. New hp: " << getInfo().hp << endl;
    } else {
        cout << "attack misses" << endl;
    }
} 

State &Player::getState() {
    return *pos;
}

void Player::setState(State newPos) {
    pos->x = newPos.x;
    pos->y = newPos.y;
} 

/*
Race Player::getRace() {
    return race;
}
*/

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

bool Player::move(Direction dir) {
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

