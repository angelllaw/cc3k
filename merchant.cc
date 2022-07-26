#include "merchant.h"
#include "info.h"
#include <iostream>

using namespace std;

bool Merchant::hostile = false;

Merchant::Merchant() {
    stats = make_unique<Info>(Info{30, 70, 5, 0});
}

Merchant::~Merchant() {}

bool Merchant::shouldAttack(State &myPos, State &otherPos) {
    if (hostile) {
        return Enemy::shouldAttack(myPos, otherPos); // should call enemy shouldAttack
    } else {
        // cout << "Merchant is not hostile." << endl;
        return false;
    }
}

int Merchant::getAttacked(int damage) {
    hostile = true;
    return Enemy::getAttacked(damage);
}

char Merchant::getChar() { return 'M'; }

bool Merchant::dropsMerchantHorde() {
    return true;
}

void Merchant::reset() {
    hostile = false;
}

bool Merchant::isHostile() {
    return hostile;
}
