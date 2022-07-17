#ifndef FLOOR_H
#define FLOOR_H

/* 
Floor should:
- iterate through all tiles to call nextTurn() on all enemies
- has a vector of 5 chambers
- has a vector of vector of tiles
 */

#include <string>
#include <vector>
#include <map>

class Tile;

class Floor {
        // TODO: add these fields to UML
        const int width = 79;
        const int height = 25;
        std::vector<std::vector<Tile>> theFloor;

        

        // needs a player pointer
        void spawnCoords();
    public:
        Floor(int width, int height);
        void updateFloor();
        void init(string map);
        void print();
        bool isValidMove(int x, int y);

};

#endif
