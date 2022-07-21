#include "info.h"
#include <iostream>
using namespace std;


void Info::add(const Info toAdd) {

    hp += toAdd.hp;
    atk += toAdd.atk;
    def += toAdd.def;
    gold += toAdd.gold;

    if (hp < 0) hp = 0;
}