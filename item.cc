#include "item.h"
#include <iostream>
using namespace std;

Item::~Item() {}

bool Item::validUse() {
    return true;
}

bool Item::isGold() {
    return false;
}
