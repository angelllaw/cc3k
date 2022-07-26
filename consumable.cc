#include "consumable.h"
#include "info.h"
#include "human.h"
#include "elf.h"
#include "dwarf.h"
#include "orc.h"
#include <string>
using namespace std;

Consumable::Consumable(ItemType item) : effect{make_unique<Info>(Info{0, 0 ,0, 0})} {
    switch (item)  {
        case ItemType::RH: // +10 HP (cannot exceed max)*
            effect->hp = 10;
            break;
        case ItemType::BA: // +5 Atk
            effect->atk = 5;
            break;
        case ItemType::BD: // + 5 Def
            effect->def = 5;
            break;
        case ItemType::PH: // -10 HP (cannot drop below 0)*
            effect->hp = -10;
            break;
        case ItemType::WA: // -5 Atk
            effect->atk = -5;
            break;
        case ItemType::WD: // -5 Def
            effect->def = -5;
            break;
        case ItemType::NormalGold: // +1 Gold
            effect->gold = 1;
            break;
        case ItemType::SmallHorde: // +2 Gold
            effect->gold = 2;
            break;
        case ItemType::MerchantHorde: // +4 Gold
            effect->gold = 4;
            break;
        /*case ItemType::DragonHorde: // +6 Gold
            effect->gold = 6;
            break;
        */
        default:
            // just to get rid of warning, if it's anything other than a consumable
            // ... something went wrong 
            break;
    }
}

void Consumable::useOn(Human *p) {
    // cout << "the potion's effect INFO:" << effect->atk << " " << effect->def << " " << effect->hp << " " << effect->gold << endl;
    p->getInfo().add(*effect);
}

// gold is doubled in value
void Consumable::useOn(Dwarf *p) {
    effect->gold *= 2;
    p->getInfo().add(*effect);
}

// negative positions have the opposite effect
void Consumable::useOn(Elf *p) {
    if (effect->hp < 0) effect->hp *= -1;
    if (effect->atk < 0) effect->atk *= -1;
    if (effect->def < 0) effect->def *= -1;
    p->getInfo().add(*effect);
} 

// gold is halved in value
void Consumable::useOn(Orc *p) {
    effect->gold /= 2;
    p->getInfo().add(*effect);
}

char Consumable::getChar() {
    if (effect->gold == 0) {
        return 'P';
    }
    return 'G';
}

bool Consumable::isGold() {
    if (effect->gold > 0) return true;
    return false;
}

string Consumable::getPotion() {
    if (effect->hp > 0) return "RH";
    if (effect->hp < 0) return "PH";
    if (effect->atk > 0) return "BA";
    if (effect->atk < 0) return "WA";
    if (effect->def > 0) return "BD";
    if (effect->def < 0) return "WD";
    return "";
}
