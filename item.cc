#include "item.h"
#include <string>
using namespace std;

Item::~Item() {}

bool Item::validUse() {
    return true;
}

bool Item::isGold() {
    return false;
}

string Item::getPotion() {
    return "";
}
