#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
using namespace std;

/* 
Floor should have:
FIELDS:
- vector<chambers *> 
- vector<vector<tile *>> stores the state of the current map. Live map of what's actually going on.
- vector<vector<char>> (the default map background)

METHODS:
- updateFloor() iterates through all tiles to call nextTurn() on all enemies
        - after moving all enemies, loop again to change hasMoved bool back to false (loop through twice in total)
- spawnCoords() randomly generates coordinates to an empty, valid tile. Returns coordinates.
- init() creates the vector<vector<tile *>>
        - will be responsible to generating the items and enemies
 */


class Player;
class Tile;
class Chamber;

class Floor {
        Player* PC;
        vector<vector<Tile *>> map;
        vector<Chamber *> chambers;
=======
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
