#ifndef CHAMBER_H
#define CHAMBER_H

#include <vector>

class Tile;

class Chamber {
    std::vector<int> tiles;

    public:
        void addTile(int idx);
        int getSize();
        int getStrIdx(int i);
};

#endif
