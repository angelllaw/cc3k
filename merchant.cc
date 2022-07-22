#include "merchant.h"
#include "info.h"
#include <iostream>

using namespace std;

bool Merchant::hostile = false;

Merchant::Merchant() {
    init(unique_ptr<Info> (new Info {30, 70, 5, 0}));
    // instead of adding 1 gold immediately to player, Merchant drops gold
    // still need to implement static hostile variable
}

Merchant::~Merchant() {}

bool Merchant::shouldAttack(State &myPos, State &otherPos) {
    if (hostile) {
        return Enemy::shouldAttack(myPos, otherPos); // should call enemy shouldAttack
    } else {
        cout << "Merchant is not hostile." << endl;
        return false;
    }
}

int Merchant::getAttacked(int damage) {
    hostile = true;
    return Enemy::getAttacked(damage);
}

char Merchant::getChar() { return 'M'; }
