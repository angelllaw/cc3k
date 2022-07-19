#include "floor.h"
#include "itemFactory.h"
#include "consumable.h"
#include "random.h"
#include "item.h"
#include "tile.h"
#include <memory>

#include <iostream>
#include "state.h" // DELETE
#include <cassert>

using namespace std;

/*
ItemFactory::ItemFactory(Floor* floor) {
    this->floor = floor;
}
*/

void ItemFactory::generatePotions(Floor &floor) {
    Random r;
    vector<ItemType> potions { ItemType::RH, ItemType::BA, ItemType::BD, ItemType::PH, ItemType::WA, ItemType::WD };

    for (int i = 0; i < 10; i++) {
        int idx = r.randomNum(6); // random potion

        ItemType cur = potions[idx];
        
        int stringIdx = r.randomStrIdx(floor); // get random string index in a random chamber
        
        Tile *toPlace = floor.getTile(stringIdx); // get tile
        cout << "tile x: " << toPlace->getState().x << endl;
        cout << "tile y: " << toPlace->getState().y << endl;
        
        assert (toPlace->getType() == TileType::MoveableTile);

        /// ERROR WITH MAKING UNIQUE OAFLJANFLJANFLJNADNKS
        
        toPlace->setItem(make_unique<Item>(Consumable(cur))); // place item
        
        
    }
}

void ItemFactory::generateTreasures(Floor &floor) {
    Random r;
    // 2. generate 10 treasures
    vector<ItemType> treasures { ItemType::NormalGold, ItemType::NormalGold, ItemType::NormalGold, ItemType::NormalGold,  
                                ItemType::NormalGold, ItemType::DragonHorde, ItemType::SmallHorde, ItemType::SmallHorde };

    for (int i = 0; i < 10; i++) {
        int idx = r.randomNum(8); // random treasure
        ItemType cur = treasures[idx];

        int stringIdx = r.randomStrIdx(floor);
        Tile *toPlace = floor.getTile(stringIdx);
        // toPlace->setItem(unique_ptr<Item> (new Consumable(cur))); 
    }
}

void ItemFactory::generateCompass(Floor &floor) {
    Random r;
    // 3. place compass
    int compassStrIdx = r.randomStrIdx(floor);
    Tile *toPlace = floor.getTile(compassStrIdx);
    // toPlace->setItem(unique_ptr<Item> (new Consumable(ItemType::Compass))); 
}


