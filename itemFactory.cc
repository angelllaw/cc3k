#include "floor.h"
#include "itemFactory.h"
#include "consumable.h"
#include "random.h"
#include "item.h"
#include "tile.h"
#include <memory>

using namespace std;

// enum class ItemType { RH, BA, BD, PH, WA, WD, NormalGold, SmallHorde, MerchantHorde, DragonHorde };

ItemFactory::ItemFactory(Floor* floor) {
    Random r;

    // 1. generate 10 potions
    vector<ItemType> potions { ItemType::RH, ItemType::BA, ItemType::BD, ItemType::PH, ItemType::WA, ItemType::WD };

    for (int i = 0; i < 10; i++) {
        int idx = r.randomNum(6);
        ItemType cur = potions[idx]; // the potion to be placed

        while (true) {
            int cIdx = r.randomNum(5);
            int sizeOfChamber = floor->getChamberSize(cIdx);
            int tileIdx = r.randomNum(sizeOfChamber);
            int stringIdx = floor->getStringIdx(cIdx, tileIdx); // now we have the string index of a specific tile
            
            if (floor->isValidMove(stringIdx)) { // tile is empty
                // construct a new cur
                unique_ptr<Item> i;
                i = unique_ptr<Item> (new Consumable(cur));
                
                // still need to set the tile to hold i =====
                // - get a reference to the tile ============
                break;
            }
        }
    }

    // 2. generate 10 treasures
}

