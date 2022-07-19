#ifndef TILE_H
#define TILE_H

#include <memory>

class Enemy;
class Item;
struct State;

enum class TileType { Empty, VWall, HWall, Passage, Door, MoveableTile };

// Since tiles "own" the enemy and item, tiles must be responsible for freeing the item / enemy after they die
class Tile {
    const State *pos;
    TileType type;
    std::unique_ptr<Item> item;
    std::unique_ptr<Enemy> enemy;

    public:
    Tile(int x, int y, TileType type);
    ~Tile();
    void removeEntities(); // frees the *item AND *enemy (calls clear). Set tile id back to 0.
    void setId(TileType newType);
    TileType getType();
    bool hasEnemy();
    bool hasItem();

    Enemy *getEnemy();
    State getState();
    void setEnemy(Enemy *e);
    void setItem(Item *i);

    friend std::ostream &operator<<(std::ostream &out, const Tile &td);
};

#endif
