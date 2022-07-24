#ifndef TILE_H
#define TILE_H

#include <memory>

class Enemy;
class Item;
struct State;

enum class TileType { Empty, VWall, HWall, Passage, Door, MoveableTile };

class Tile {
    const std::unique_ptr<State> pos;
    TileType type;
    std::unique_ptr<Item> item;
    std::unique_ptr<Enemy> enemy;
    
    public:
    Tile(int x, int y, TileType type);
    ~Tile();
    void removeEntities(); // frees the *item AND *enemy (calls clear).
    void setId(TileType type);
    TileType getType();
    State getState();

    bool hasEnemy();
    bool hasItem();
    std::unique_ptr<Enemy> &getEnemy();
    std::unique_ptr<Item> &getItem();
    void moveEnemy(std::unique_ptr<Enemy> &other);
    void moveItem(std::unique_ptr<Item> &other);
    
    friend std::ostream &operator<<(std::ostream &out, const Tile &td);
};

#endif
