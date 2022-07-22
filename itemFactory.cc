#include "floor.h"
#include "itemFactory.h"
#include "consumable.h"
#include "random.h"
#include "item.h"
#include "tile.h"
#include "dragonHorde.h"
#include "dragon.h"
#include "enemy.h" // necessary?
#include <memory>

#include <iostream>
#include "state.h" // DELETE
#include <cassert>

using namespace std;

void ItemFactory::generatePotions(Floor &floor) {
    Random r;
    vector<ItemType> potions { ItemType::RH, ItemType::BA, ItemType::BD, ItemType::PH, ItemType::WA, ItemType::WD };

    for (int i = 0; i < 10; i++) {
        int idx = r.randomNum(6); // random potion
        ItemType cur = potions[idx];
        
        int stringIdx = r.randomStrIdx(floor); // get random string index in a random chamber
        Tile *toPlace = floor.getTile(stringIdx); // get tile
        assert (toPlace->getType() == TileType::MoveableTile);
        
        unique_ptr<Item> item (new Consumable{cur});
        toPlace->moveItem(item); // place item
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

        if (cur == ItemType::DragonHorde) {
            cout << "about to make dragonHorde" << endl;
            int itemIdx;
            int dragonIdx;
            while (true) {
                itemIdx = r.randomStrIdx(floor);
                dragonIdx = floor.rNeighbourStrIdx(itemIdx,floor);
                if (dragonIdx != -1) break;
            }
            Tile *toPlaceItem = floor.getTile(itemIdx);
            Tile *toPlaceDragon = floor.getTile(dragonIdx);
            assert (toPlaceItem->getType() == TileType::MoveableTile);
            assert (toPlaceDragon->getType() == TileType::MoveableTile);

            DragonBaby *db = new DragonHorde; // have to set the identifier!
            Dragon *dragon = new Dragon;
            dragon->setDragonBaby(db);
            db->setDragonMomma(dragon);

            unique_ptr<Item> item (db); // needs to take a pointer to a dragon
            unique_ptr<Enemy> enemy (dragon); // needs to take a pointer to a dragonBaby
            toPlaceItem->moveItem(item); // place item
            toPlaceDragon->moveEnemy(enemy);

        } else {
            int stringIdx = r.randomStrIdx(floor); // get random string index in a random chamber
            Tile *toPlace = floor.getTile(stringIdx); // get tile
            assert (toPlace->getType() == TileType::MoveableTile);
            unique_ptr<Item> item (new Consumable{cur});
            toPlace->moveItem(item); // place item
        }
    }
}


