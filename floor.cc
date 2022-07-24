#include "floor.h"
#include "tile.h"
#include "chamber.h"
#include "state.h"
#include "info.h"
#include "player.h"
#include "enemy.h"
#include "random.h"
#include "itemFactory.h"
#include "enemyFactory.h"
#include "direction.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

#include <cassert>
#include <cmath>

using namespace std;

int Floor::floorNum = 0;

Floor::Floor(shared_ptr<Player> pc, string numMap, string floorMap, bool hasLayout) : pc{pc} {
    setChambers(numMap);
    floorNum++;
    init(floorMap, hasLayout);
}

TileType getTileId(char c) {
    if (c == ' ') return TileType::Empty;
    if (c == '-') return TileType::HWall;
    if (c == '|') return TileType::VWall;
    if (c == '#') return TileType::Passage; 
    if (c == '+') return TileType::Door; 
    return TileType::MoveableTile;
}


void Floor::spawn() {
    
    // 1. spawn stairs
    Random r;
    int stairsIdx = r.randomStrIdx(*this);
    stairs = idxToPos(stairsIdx);

    // 2. spawn potions and treasures
    ItemFactory iFactory;
    iFactory.generatePotions(*this);
    iFactory.generateTreasures(*this);
    
    // 3. spawn enemies
    EnemyFactory eFactory;
    eFactory.generateEnemies(*this);
}

void Floor::layout(string map) {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            char c = map[row * width + col];
            switch(c) {
                case '@':
                    pc->setState(State{col, row}); // might cause error (check)
                    break;
                case '0': // RH potion
                    break;
                case '1': // BA potion
                    break;
                case '2': // BD potion
                    break;
                case '3': // PH potion
                    break;
                case '4': // WA potion
                    break;
                case '5': // WD potion
                    break;
                case '6': // normal gold pile
                    break;
                case '7': // small gold pile
                    break;
                case '8': // merchant horde
                    break;
                case '9': // dragon horde
                    break;
                // enemies
                case 'V':
                    break;
                case 'W':
                    break;
                case 'T':
                    break;
                case 'N':
                    break;
                case 'M':
                    break;
                case 'D':
                    break;
                case 'X':
                    break;
                default:
                    cout << "what the fuck is this L symbol" << endl;
            }
        }
    }
}

// reads in a string map and sets "theFloor" tile IDs
void Floor::init(string map, bool hasLayout) {
    // generate the actual floor & tiles
    for (int row = 0; row < height; row++) {
        vector<Tile *> tmp;
        for (int col = 0; col < width; col++) {
            char c = map[row * width + col];
            tmp.emplace_back(new Tile(col, row, getTileId(c)));
        }
        theFloor.emplace_back(tmp);
    }

    if (!hasLayout) {
        spawn();
    } else {
        layout(map);
    }
}

void Floor::print(string action) {
    for (auto &row : theFloor) {
        for (auto &col : row) {
            int curX = col->getState().x;
            int curY = col->getState().y;

            if (curX == pc->getState().x && curY == pc->getState().y) { // player
                cout << "\033[36m" << '@' << "\033[0m";
            } else if (curX == stairs.x && curY == stairs.y) { // stairs
                if (pc->hasCompass()) {
                    cout << "\033[32m" << '\\' << "\033[0m";
                } else {
                    cout << "\033[33m" << '\\' << "\033[0m";
                }
                // char print = pc->hasCompass() ? '.' : '\\'; cout << print;
            } else {
                cout << *col;
            }

        }
        cout << endl;
    }

    // print message
    cout << "Race: " << pc->printRace();
    cout << " Gold: " << pc->getInfo().gold; 
    cout << setw(55) << right << "Floor " << floorNum << endl;
    cout << "HP: " << pc->getInfo().hp << endl;
    cout << "Atk: " << pc->getInfo().atk << endl;
    cout << "Def: " << pc->getInfo().def << endl;

    cout << action << endl;
}

// invariant: chambers are numbered 1...x
void Floor::setChambers(string map) {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            int idx = row * width + col;
            char c = map[idx];
            if ('0' <= c && c <= '9') {
                if ((c - '0') > (int)chambers.size()) {
                    chambers.emplace_back(new Chamber{});
                    // cout << "created new chamber" << endl;
                }
                chambers[c - '0' - 1]->addTile(idx);
                // cout << "added (" << col << ", " << row << ") to chamber " << c - '0' - 1 << endl;
            }
        }
    }
}

// returns the coordinates of the 
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

void Floor::updateFloor(string action) {
    for (auto &row : theFloor) {
        for (auto &tile : row) {
            // update floor tile by tile

            // 1. if enemy, try to attack, if can't, then move
            if (tile->hasEnemy()) { // if tile has an enemy and enemy has not moved
                unique_ptr<Enemy> &curEnemy = tile->getEnemy();
                if (curEnemy->isDead()) {
                    int goldReward = curEnemy->goldUponDead();
                    pc->addGold(goldReward);
                    cout << "Earned " << goldReward << " from killing " << curEnemy->getChar() << endl;
                    tile->removeEntities(); // drops gold? adds gold?
                    continue;
                } else if (curEnemy->hasMoved) {
                    continue;
                }
                // cout << "tile " << tile->getState().x << ", " << tile->getState().y << " has enemy " << *tile << endl;
                State curPos = tile->getState();
                //cout << "Can enemy attack? ";
                if (curEnemy->shouldAttack(curPos, pc->getState())) { // checks if it can attack
                    //cout << "Yes" << endl;
                    action += curEnemy->getChar();
                    Random r;
                    if (r.randomNum(2) == 0) {
                        action += " deals ";

                        int damage = curEnemy->attack(*pc);
                        stringstream ss;
                        ss << damage;
                        action += ss.str();

                        action += " damage to PC. ";
                    } else {
                        action += " misses. ";
                    }
                } else {
                    // cout << "No" << endl;
                    // randomly move
                    State newPos;
                    vector<int> neighbors = Random{}.randomArr(8);

                    for (int i = 0; i < (int)neighbors.size(); ++i) {
                        Direction dir = Direction(neighbors[i]);
                        newPos = getCoords(curPos, dir);
                        if (isValidMove(newPos)) break; // tile is empty movable tile
                    }
                    // move enemy to state s.
                    // set hasMoved to true
                    curEnemy->toggleMove(); // set hasMoved to true

                    assert (0 <= newPos.y && newPos.y < height);
                    assert (0 <= newPos.x && newPos.x < width);

                    Tile *newTile = theFloor[newPos.y][newPos.x];

                    assert (newTile->getType() == TileType::MoveableTile);

                    newTile->moveEnemy(curEnemy);
                    // newTile points to this enemy
                    // set this tile to point to nothing
                }
            }
        }
    }
    // loop through again to reset hasMoved boolean
    for (auto &row : theFloor) {
        for (auto &tile : row) {
            if (tile->hasEnemy() && tile->getEnemy()->hasMoved) { // if tile has enemy and hasMoved=true
                tile->getEnemy()->toggleMove();
            }
        }
    }
    print(action);
}

bool Floor::isValidMove(State &pos) {
    Tile *t = theFloor[pos.y][pos.x];
    State &pcPos = pc->getState();
    if (pcPos.y == pos.y && pcPos.x == pos.x) return false; // on player
    if (pos.x == stairs.x && pos.y == stairs.y) return false; // on stairs
    return t->getType() == TileType::MoveableTile && !t->hasEnemy() && !t->hasItem(); 
}

bool Floor::isValidMove(int idxNum) {
    State pos = idxToPos(idxNum);
    return isValidMove(pos);
}

int Floor::validPlayerTile(State &pos) {
    Tile *t = theFloor[pos.y][pos.x];
    TileType type = t->getType();
    // Empty, VWall, HWall
    if (type == TileType::Empty || type == TileType::VWall || type == TileType::HWall) {
        return 0;
    // Moveable Tile, Potion or Enemy is on it
    } else if (type == TileType::MoveableTile) { 
        if (t->hasEnemy()) return -1;
        if (t->hasItem()) {
            if (t->hasGold()) {
                // pc->useItem(t->getItem());
            }
        }
    } else if (pos.x == stairs.x && pos.y == stairs.y) {
        // STAIRS
    } else {
        return 1; // must be valid Passage, Door, MoveableTile 
    }
}

int Floor::getChamberSize(int idx) {
    return chambers[idx]->getSize();
}

int Floor::getNumChambers() {
    return chambers.size();
}

int Floor::getStringIdx(int chamber, int idx) {
    return chambers[chamber]->getStrIdx(idx);
}

State Floor::idxToPos(int idx) {
    int x = idx % width;
    int y = (idx - x) / width;
    return {x, y};
}

Tile *Floor::getTile(int idxNum) {
    State pos = idxToPos(idxNum);
    return theFloor[pos.y][pos.x];
}

Tile *Floor::getTile(State pos) {
    return theFloor[pos.y][pos.x];
}


State Floor::getState(State &curPos, Direction dir) {
    return getCoords(curPos, dir);
}

Item* Floor::getItem(State &itemPos) {
    Item *i = getTile(itemPos)->getItem().get();
    return i;
}

void Floor::removeItem(State pos) {
    if (getTile(pos)->getItem()->validUse()) getTile(pos)->removeEntities();
}

// Returns a random neighbour tile's string index. If there are none, returns -1.
int Floor::rNeighbourStrIdx(int strIdx, Floor &floor) {
    vector<int> v = Random{}.randomArr(8); // shuffle an array from 1-7

    for (int i = 0; i < 8; i++) {
        Direction d = Direction(v[i]); // random direction
        State givenPos = idxToPos(strIdx); // convert to State
        State candidatePos = getState(givenPos, d); // current state + direction
        if (isValidMove(candidatePos)) { // is empty?
            return candidatePos.x + candidatePos.y * width;
        }
    }
    return -1;
}

bool Floor::onStairs() {
    State pos = pc->getState();
    return stairs.x == pos.x && stairs.y == pos.y;
}
