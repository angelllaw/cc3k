#ifndef TILE_H
#define TILE_H

#include <memory>

class Enemy;
class Item;

// TILE IDENTIFIERS:
// 0 - empty space ( )
// 1 - vertical wall (-)
// 2 - horizental wall (|)
// 3 - passage (#)
// 4 - door (+)
// 5 - points to item (item pointer will be not a nullptr)
// 6 - points to enemy (enemy pointer will be not a nullptr)

// Since tiles "own" the enemy and item, tiles must be responsible for freeing the item / enemy after they die
class Tile {
    int x;
    int y;
    int id;
    std::unique_ptr<Item> item;
    std::unique_ptr<Enemy> enemy;
    public:
    Tile(int x, int y, int id);
    void removeEntities(); // frees the *item AND *enemy. Set tile id back to 0.
};

#endif
