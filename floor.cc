#include "floor.h"
#include "tile.h"

#include <string>
#include <sstream>
#include <vector>
using namespace std;

void Floor::init() {
    string defaultMap = 
    "|-----------------------------------------------------------------------------|"
    "|                                                                             |"
    "| |--------------------------|        |-----------------------|               |"
    "| |..........................|        |.......................|               |"
    "| |..........................+########+.......................|-------|       |"
    "| |..........................|   #    |...............................|--|    |"
    "| |..........................|   #    |..................................|--| |"
    "| |----------+---------------|   #    |----+----------------|...............| |"
    "|            #                 #############                |...............| |"
    "|            #                 #     |-----+------|         |...............| |"
    "|            #                 #     |............|         |...............| |"
    "|            ###################     |............|   ######+...............| |"
    "|            #                 #     |............|   #     |...............| |"
    "|            #                 #     |-----+------|   #     |--------+------| |"
    "|  |---------+-----------|     #           #          #              #        |"
    "|  |.....................|     #           #          #         |----+------| |"
    "|  |.....................|     ########################         |...........| |"
    "|  |.....................|     #           #                    |...........| |"
    "|  |.....................|     #    |------+--------------------|...........| |"
    "|  |.....................|     #    |.......................................| |"
    "|  |.....................+##########+.......................................| |"
    "|  |.....................|          |.......................................| |"
    "|  |---------------------|          |---------------------------------------| |"
    "|                                                                             |"
    "|-----------------------------------------------------------------------------|";
    istringstream iss(defaultMap);

    char c;
    int id;

    for (int y = 0; y < 25; y++) {
        vector<Tile *> tmp;
        for (int x = 0; x < 79; x++) {
            iss >> c;
            if (c == ' ') id = 0; 
            if (c == '-') id = 1;
            if (c == '|') id = 0;
            if (c == '#') id = 0;
            if (c == '+') id = 0;
            tmp.push_back(new Tile(x, y, id));
        }
        map.push_back(tmp);
    }    
}

// how do we initialize our floor to have the default map.
// idea: have a string with our default map
// make the string into a stringstream, and read off one char at a time to populate the vector we want to initialize
=======
#include <iostream>
using namespace std;

Floor::Floor(int width, int height) : width{width}, height{height}, theFloor{vector<vector<Tile>>(height)} {
    for (auto &row : theFloor) {
        for (int col = 0; col < width; ++col) {
            row.emplace_back(Tile{}); // Q: does Tile need to be a pointer? or else will it be popped off the stack?
        }
    }
    // results in an empty width x height grid of Tiles
}

// reads in a string map and sets "theFloor" tile IDs
void Floor::init(string map) {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            // set tile id to whatever the char is
            char c = map[row * width + col]; // TODO: check if this formula is right

            theFloor[row][col].setId(c); // TODO: change c to be a specific ID num (im just lazy)
        }
    }
}

void Floor::print() {
    for (auto &row : theFloor) {
        for (auto &col : row)
            cout << col; // TODO: implement the override for tile "<<" operator
    }
}
