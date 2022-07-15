#ifndef FLOOR_H
#define FLOOR_H

/* 
Floor should:
- iterate through all tiles to call nextTurn() on all enemies
- has a vector of 5 chambers
- has a vector of vector of tiles
 */

class Floor {
        // needs a player pointer
        void spawnCoords();
    public:
        void updateFloor();
        void init();
        void print();
        bool isValidMove(int x, int y);

};

#endif
