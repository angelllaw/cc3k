#ifndef TILE_H
#define TILE_H

class Enemy;
class Item;

class Tile {
    int x;
    int y;
    int id;
    Item *item;
    Enemy *enemy;
};

#endif
