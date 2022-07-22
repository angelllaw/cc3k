#include "floor.h"
#include "enemyFactory.h"
#include "random.h"
#include "enemy.h"
#include "tile.h"

#include "werewolf.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "phoenix.h"
#include "merchant.h"
#include "compass.h"

#include <memory>
#include <iostream>
#include <cassert>

using namespace std;

unique_ptr<Enemy> initializeEnemy(EnemyType type) {
    switch (type) {
        case EnemyType::Werewolf:
            return unique_ptr<Enemy> (new Werewolf());
        case EnemyType::Vampire:
            return unique_ptr<Enemy> (new Vampire());
        case EnemyType::Goblin:
            return unique_ptr<Enemy> (new Goblin());
        case EnemyType::Troll:
            return unique_ptr<Enemy> (new Troll());
        case EnemyType::Phoenix:
            return unique_ptr<Enemy> (new Phoenix());
        case EnemyType::Merchant:
            return unique_ptr<Enemy> (new Merchant());
        default:
            return unique_ptr<Enemy> (nullptr);
    }
}

void EnemyFactory::generateEnemies(Floor &floor) {
    Random r;
    vector<EnemyType> enemies { EnemyType::Werewolf, EnemyType::Werewolf, EnemyType::Werewolf, EnemyType::Werewolf, 
                                EnemyType::Vampire, EnemyType::Vampire, EnemyType::Vampire, 
                                EnemyType::Goblin, EnemyType::Goblin, EnemyType::Goblin, EnemyType::Goblin, EnemyType::Goblin, 
                                EnemyType::Troll, EnemyType::Troll, 
                                EnemyType::Phoenix, EnemyType::Phoenix,
                                EnemyType::Merchant, EnemyType::Merchant };
    // 20 enemies spawned per floor.
    for (int i = 0; i < 20; i++) {
        int idx = r.randomNum(18); // random enemy
        EnemyType type = enemies[idx];
        
        int stringIdx = r.randomStrIdx(floor); // get random string index in a random chamber
        Tile *toPlace = floor.getTile(stringIdx); // get tile
        assert (toPlace->getType() == TileType::MoveableTile);

        unique_ptr<Enemy> enemy = initializeEnemy(type);

        if (i == 0) {
            unique_ptr<Compass> c (new Compass);
            cout << "enemy has compass. enemy at :" << toPlace->getState().x << " " << toPlace->getState().y << endl;
            enemy->setCompass(c);
        }
        toPlace->moveEnemy(enemy);
        
    }
    Tile *toTest = floor.getTile(240); // get tile
    unique_ptr<Item> c (new Compass);
    toTest->moveItem(c);
}