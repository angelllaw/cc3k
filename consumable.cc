#include "consumable.h"
#include "info.h"

// enum class ItemType { RH, BA, BD, PH, WA, WD, NormalGold, SmallHorde, MerchantHorde, DragonHorde };

Consumable::Consumable(ItemType item) {

    // initialize effect
    effect->hp = 0;
    effect->atk = 0;
    effect->def = 0;
    effect->gold = 0;

    switch (item)  {
        // potions
        case ItemType::RH: // +10 HP (cannot exceed max)*
            id = ItemType::RH;
            effect->hp = 10;
            break;
        case ItemType::BA: // +5 Atk
            id = ItemType::BA;
            effect->atk = 5;
            break;
        case ItemType::BD: // + 5 Def
            id = ItemType::BD;
            effect->def = 5;
            break;
        case ItemType::PH: // -10 HP (cannot drop below 0)*
            id = ItemType::PH;
            effect->hp = -10;
            break;
        case ItemType::WA: // -5 Atk
            id = ItemType::WA;
            effect->atk = -5;
            break;
        case ItemType::WD: // -5 Def
            id = ItemType::WD;
            effect->def = -5;
            break;
        // gold
        case ItemType::NormalGold: // +1 Gold
            id = ItemType::NormalGold;
            effect->gold = 1;
            break;
        case ItemType::SmallHorde: // +2 Gold
            id = ItemType::SmallHorde;
            effect->gold = 2;
            break;
        case ItemType::MerchantHorde: // +4 Gold
            id = ItemType::MerchantHorde;
            effect->gold = 4;
            break;
        case ItemType::DragonHorde: // +6 Gold
            id = ItemType::DragonHorde;
            effect->gold = 6;
            break;
    }
}


