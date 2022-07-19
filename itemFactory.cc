#include "floor.h"
#include "itemFactory.h"
#include "consumable.h"
#include "random.h"
#include "item.h"
#include "tile.h"
#include <memory>

using namespace std;


ItemFactory::ItemFactory(Floor* floor) {
    Random r;
    // 1. generate 10 potions
    vector<ItemType> potions { ItemType::RH, ItemType::BA, ItemType::BD, ItemType::PH, ItemType::WA, ItemType::WD };

    for (int i = 0; i < 10; i++) {
        int idx = r.randomNum(6); // random potion
        ItemType cur = potions[idx];

        int stringIdx = r.randomStrIdx(floor); // get random valid string index
        Tile *toPlace = floor->getTile(stringIdx); // get tile
        toPlace->setItem(unique_ptr<Item> (new Consumable(cur))); // place item
    }

    // 2. generate 10 treasures
    vector<ItemType> treasures { ItemType::NormalGold, ItemType::NormalGold, ItemType::NormalGold, ItemType::NormalGold,  
                                ItemType::NormalGold, ItemType::DragonHorde, ItemType::SmallHorde, ItemType::SmallHorde };

    for (int i = 0; i < 10; i++) {
        int idx = r.randomNum(8); // random treasure
        ItemType cur = treasures[idx];

        int stringIdx = r.randomStrIdx(floor);
        Tile *toPlace = floor->getTile(stringIdx);
        toPlace->setItem(unique_ptr<Item> (new Consumable(cur))); 
    }

    // 3. place compass
    int compassStrIdx = r.randomStrIdx(floor);
    Tile *toPlace = floor->getTile(compassStrIdx);
    toPlace->setItem(unique_ptr<Item> (new Consumable(ItemType::Compass)));

}

