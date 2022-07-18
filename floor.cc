#include "floor.h"
#include "tile.h"

#include <vector>
#include <iostream>
using namespace std;

// how do we initialize our floor to have the default map.
// idea: have a string with our default map
// make the string into a stringstream, and read off one char at a time to populate the vector we want to initialize

Floor::Floor(int width, int height) : width{width}, height{height} {}

int getTileId(char c) {
    int id = 0;
    if (c == ' ') id = 0; 
    if (c == '-') id = 1;
    if (c == '|') id = 0;
    if (c == '#') id = 0;
    if (c == '+') id = 0;
    return 0;
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
        for (auto &col : row)
            cout << col; // TODO: implement the override for tile "<<" operator
    }
}
