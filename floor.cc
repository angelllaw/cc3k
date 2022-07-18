#include "floor.h"
#include "tile.h"
#include "chamber.h"

#include <vector>
#include <map>
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

// NOTE: in this fn, tiles vector in Chamber class contains ints which are the idx in the string
void Floor::setChambers(string floorMap) {    
    int chamberNum = 0;
    map<int, int> chamberMap;
        // key: idx
        // val: chamberNum
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            int idx = row * width + col;
            char c = floorMap[idx];
            if (c == '.') {
                // check if theres neighboring '.' 
                bool hasNeighbor = false;
                for (int y = row - 1; y <= row + 1 && y >= 0 && y < height; ++y) {
                    for (int x = col - 1; x <= col + 1 && x >= 0 && x < width; ++x) {
                        if (row == y && col == x) continue;
                        int neighborIdx = y * width + x;
                        if (floorMap[neighborIdx] == '.') {
                            hasNeighbor = true;
                            cout << "found neighbor at (" << x << ", " << "y)" << endl;
                            // the first '.' we come acros should be in the map
                            // val = chamberNum of neighborIdx
                            // add this idx to tile vector in chamber[val]
                            chambers[chamberMap[neighborIdx]]->tiles.emplace_back(idx);
                            cout << "adding " + idx + " to chamber " + chamberMap[neighborIdx] << endl; 
                            // then add this idx to map with same val as neighbor idx
                            chamberMap[idx] = chamberMap[neighborIdx];
                            break;
                            // TODO: break out of nested for loop
                        }
                    }
                    if (hasNeighbor) break;
                }
                if (!hasNeighbor) {
                    // this '.' is the first in the chamber
                    chamberMap[idx] = chamberNum; // add idx to map
                    // create new chamber and add to chamber array
                    chambers.emplace_back(new Chamber{});
                    cout << "created new chamber" << endl;
                    // add idx to tiles vector
                    chambers[chamberNum]->tiles.emplace_back(idx);
                    cout << "adding " + idx + " to chamber " + chamberNum << endl; 
                    ++chamberNum;
                }
            }
        }
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

