#ifndef RANDOM_H
#define RANDOM_H

#include <vector>

class Floor;

class Random {
    public:
        int randomNum(int bottom, int top);
        int randomNum(int top);
        int randomStrIdx(Floor &floor); // returns an empty moveable Tile string index
        int rNeighbourStrIdx(int strIdx, Floor &floor); // returns a random neighbours stringIdx, if none, returns -1
        std::vector<int> randomArr(int top);
};

#endif
