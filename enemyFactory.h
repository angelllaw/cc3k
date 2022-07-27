#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include <memory>

enum class EnemyType { Dragon, Vampire, Werewolf, Troll, Goblin, Merchant, Phoenix };

class Floor;
class Enemy;

class EnemyFactory {
   public:
    void generateEnemies(Floor &floor);
    std::unique_ptr<Enemy> initializeEnemy(EnemyType type);
};

#endif
