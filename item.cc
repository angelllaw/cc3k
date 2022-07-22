#include "item.h"
#include <iostream>
using namespace std;

Item::~Item() {}

// enum class ItemType { RH, BA, BD, PH, WA, WD, NormalGold, SmallHorde, MerchantHorde, DragonHorde, DragonBaby, Compass };
/* 
std::ostream &operator<<(std::ostream &out, const Item &i) {
    switch (i.id) {
        case ItemType::NormalGold:
        case ItemType::SmallHorde:
        case ItemType::MerchantHorde:
        case ItemType::DragonHorde: 
            out << 'G';
            break;
        default: // potions
            out << 'P';
            break;
    }
    return out;
}
 */