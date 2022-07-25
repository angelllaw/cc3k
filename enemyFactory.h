#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include <memory>

class Floor;
class Enemy;
enum class EnemyType;

class EnemyFactory {
    
    public:
    void generateEnemies(Floor &floor);
    std::unique_ptr<Enemy> initializeEnemy(EnemyType type);
};

#endif
