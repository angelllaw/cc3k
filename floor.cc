#include "floor.h"
#include "tile.h"

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

// how do we initialize our floor to have the default map.
// idea: have a string with our default map
// make the string into a stringstream, and read off one char at a time to populate the vector we want to initialize

Floor::Floor(int width, int height) : width{width}, height{height} {
    init(defaultMap);
}

TileType getTileId(char c) {
    TileType type = TileType::Empty;
    if (c == '-') type = TileType::HWall;
    if (c == '|') type = TileType::VWall;
    if (c == '#') type = TileType::Passage; 
    if (c == '+') type = TileType::Door; 
    if (c == '.') type = TileType::MoveableTile; // if (0 < c < 6) ?
    return type;
}

// reads in a string map and sets "theFloor" tile IDs
void Floor::init(string map) {

    for (int row = 0; row < height; row++) {
        vector<Tile *> tmp;
        for (int col = 0; col < width; col++) {
            char c = map[row * width + col];
            tmp.push_back(new Tile(row, col, getTileId(c)));
        }
        theFloor.push_back(tmp);
    }
}

void Floor::print() {
    for (auto &row : theFloor) {
        for (auto &col : row) {
            cout << *col;
        }
        cout << endl;
    }
}

// This is an extremely expensive and dumb way of generating random numbers
// This works well for returning a random element in an Array
//    - for returning a tile in a Chamber array..
//    - for returning a direction in a direction Enum
//    - for returning a chamber in a floor array of chambers
int Floor::randomNum(int bottom, int top) {
    vector<int> v;
    for (int i = bottom; i < top; i++) { v.push_back(i); }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    return v[0];
}

