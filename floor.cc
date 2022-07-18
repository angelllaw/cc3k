#include "floor.h"
#include "tile.h"
#include "chamber.h"

#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// how do we initialize our floor to have the default map.
// idea: have a string with our default map
// make the string into a stringstream, and read off one char at a time to populate the vector we want to initialize

Floor::Floor(int width, int height) : width{width}, height{height} {
    init(floorMap);
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

/*
// NOTE: in this fn, tiles vector in Chamber class contains ints which are the idx in the string
// BUG: if the idx cannot find any neighbors in the dict map, it makes a new chamber
void Floor::setChambers(string floorMap) {    
    int chamberNum = 0;
    map<int, int> chamberMap;
        // key: idx
        // val: chamberNum
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            int idx = row * width + col;
            cout << "idx: " << idx << endl;
            char c = floorMap[idx];
            if (c == '.') {
                // check if theres neighboring '.' 
                bool hasNeighbor = false;
                for (int y = row - 1; y <= row + 1 && y >= 0 && y < height; ++y) {
                    for (int x = col - 1; x <= col + 1 && x >= 0 && x < width; ++x) {
                        if (row == y && col == x) continue;
                        int neighborIdx = y * width + x;
                        if (floorMap[neighborIdx] == '.' && chamberMap.count(neighborIdx) != 0) {
                            // if neighbor is a '.' and is in the dict map
                            hasNeighbor = true;
                            cout << "found neighbor at (" << x << ", " << y << ")" << endl;
                            // val = chamberNum of neighborIdx
                            // add this idx to tile vector in chamber[val]
                            chambers[chamberMap[neighborIdx]]->addTile(idx);
                            cout << "adding " << "(" << row << ", " <<  col <<")" << " to chamber " << chamberMap[neighborIdx] << endl; 
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
                    chambers[chamberNum]->addTile(idx);
                    cout << "adding " << "(" << row << ", " <<  col <<")" << " to chamber " << chamberNum << endl; 
                    ++chamberNum;
                }
            }
        }
    }
} */

// Benry's way
// invariant: chambers are numbered 1...x
void Floor::setChambers(string map) {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            int idx = row * width + col;
            char c = map[idx];
            if ('0' <= c && c <= '9') {
                if ((c - '0') > chambers.size()) {
                    chambers.emplace_back(new Chamber{});
                    // cout << "created new chamber" << endl;
                }
                chambers[c - '0' - 1]->addTile(idx);
                // cout << "added (" << col << ", " << row << ") to chamber " << c - '0' - 1 << endl;
            }
        }
    }
}

