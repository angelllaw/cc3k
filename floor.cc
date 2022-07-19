#include "floor.h"
#include "tile.h"
#include "chamber.h"
#include "state.h"
#include "player.h"
#include "enemy.h"
#include "random.h"
#include "direction.h"

#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>

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

    // generate the actual floor & tiles
    for (int row = 0; row < height; row++) {
        vector<Tile *> tmp;
        for (int col = 0; col < width; col++) {
            char c = map[row * width + col];
            tmp.emplace_back(new Tile(row, col, getTileId(c)));
        }
        theFloor.emplace_back(tmp);
    }
    // 1. spawn player character location
    // 2. spawn stairway location
    // 3. a) spawn potions & gold
    // 3. b) spawn enemies

}

void Floor::print() {
    for (auto &row : theFloor) {
        for (auto &col : row) {
            cout << *col;
        }
        cout << endl;
    }
}

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

bool shouldAttack(const State &myPos, const State &otherPos) {
    int xDist = myPos.x - otherPos.x;
    int yDist = myPos.y - otherPos.y;
    return abs(xDist) <= 1 && abs(yDist) <= 1;
}

// TODO: Check the arithmetic is right for each dir
State getCoords(State &curPos, Direction dir) {
    State s;
    switch(dir) {
        case Direction::N:
            s = {curPos.x, curPos.y - 1};
            break;
        case Direction::NE:
            s = {curPos.x + 1, curPos.y - 1};
            break;
        case Direction::E:
            s = {curPos.x + 1, curPos.y};
            break;
        case Direction::SE:
            s = {curPos.x + 1, curPos.y + 1};
            break;
        case Direction::S:
            s = {curPos.x, curPos.y + 1};
            break;
        case Direction::SW:
            s = {curPos.x - 1, curPos.y + 1};
            break;
        case Direction::W:
            s = {curPos.x - 1, curPos.y};
            break;
        case Direction::NW:
            s = {curPos.x - 1, curPos.y - 1};
            break;
    }
    return s;
}

void Floor::updateFloor() {
    for (auto &row : theFloor) {
        for (auto &tile : row) {
            // update floor tile by tile

            // 1. if enemy, try to attack, if can't, then move
            if (tile->hasEnemy() && !tile->getEnemy()->hasMoved) {
                State curPos = tile->getState();
                if (shouldAttack(curPos, pc->getState())) {
                    tile->getEnemy()->attack(*pc);
                } else {
                    // randomly move
                    State newPos;
                    vector<int> neighbors = Random{}.randomArr(8);

                    for (int i = 0; i < neighbors.size(); ++i) {
                        Direction dir = Direction(neighbors[i]);
                        newPos = getCoords(curPos, dir);
                        if (isValidMove(newPos)) break; // tile is empty movable tile
                    }
                    // move enemy to state s.
                    // set hasMoved to true
                    tile->getEnemy()->toggleMove(); // set hasMoved to true
                    Tile *newTile = theFloor[newPos.y][newPos.x];
                    newTile->setEnemy(tile->getEnemy()); // newTile points to this enemy
                    tile->setEnemy(nullptr); // set this tile to point to nothing
                }
            } // else if
        }
    }
}

bool Floor::isValidMove(State &pos) {
    Tile *t = theFloor[pos.y][pos.x];
    return t->getType() == TileType::MoveableTile && !t->hasEnemy() && !t->hasItem(); 
}

int Floor::getChamberSize(int idx) {
    return chambers.at(idx)->getSize();
}

int Floor::getStringIdx(int chamber, int idx) {
    return chambers.at(chamber)->getStrIdx(idx);
}

Tile* Floor::getTile(int idxNum) {
    int x = idxNum % width;
    int y = (idxNum - x) / height;
    return theFloor.at(y).at(x);
}

bool Floor::isValidMove(int idxNum) {
    int x = idxNum % width;
    int y = (idxNum - x) / height;
    State s{x, y};
    return isValidMove(s);
}

