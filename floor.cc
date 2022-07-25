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
#include "consumable.h"
#include "dragon.h"
#include "dragonHorde.h"
#include "barrierSuit.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>

#include <cassert>
#include <cmath>

using namespace std;

Floor::Floor(shared_ptr<Player> pc, string numMap, string floorMap, bool hasLayout, int floorNum) 
    : pc{pc}, floorNum{floorNum}, stairs{0, 0} {
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

    // 2. spawn player
    State pos;
    while (true) {
        int idx = r.randomStrIdx(*this);
        pos = idxToPos(idx);
        if (abs(pos.x - stairs.x) > 1 && abs(pos.y - stairs.y) > 1) break;
    }
    pc->setState(pos);

    // 3. spawn potions and treasures
    ItemFactory iFactory;
    iFactory.generatePotions(*this);
    iFactory.generateTreasures(*this);
    
    // 4. spawn enemies
    EnemyFactory eFactory;
    eFactory.generateEnemies(*this);
}

void Floor::layout(string map) {
    vector<State> enemyPosArr;
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            Tile *cur = theFloor[row][col].get();
            char c = map[row * width + col];
            if (c == '@') {
                pc->setState(State{col, row});
            } else if ('0' <= c && c < '9') { // ignore dragon horde
                ItemType type;
                switch (c) {
                    case '0': // RH potion
                        type = ItemType::RH;
                        break;
                    case '1': // BA potion
                        type = ItemType::BA;
                        break;
                    case '2': // BD potion
                        type = ItemType::BD;
                        break;
                    case '3': // PH potion
                        type = ItemType::PH;
                        break;
                    case '4': // WA potion
                        type = ItemType::WA;
                        break;
                    case '5': // WD potion
                        type = ItemType::WD;
                        break;
                    case '6': // normal gold pile
                        type = ItemType::NormalGold;
                        break;
                    case '7': // small gold pile
                        type = ItemType::SmallHorde;
                        break;
                    case '8': // merchant horde
                        type = ItemType::MerchantHorde;
                        break;
                }
                unique_ptr<Item> item = make_unique<Consumable>(type);
                cur->moveItem(item);
            } else if (c == '.' || c == 'B' || c == '9') { // ignore barrier suit or dragon horde
                continue;
            } else if (c == '\\') { // stairs
                stairs = {col, row};
            } else if (c == 'D') { // dragon! Invariant: dragon only has one baby
                enemyPosArr.emplace_back(State{col, row});
                DragonBaby *baby;
                bool foundBaby = false;
                for (int dRow = row - 1; dRow >= 0 && dRow < height && dRow <= row + 1; ++dRow) {
                    for (int dCol = col - 1; dCol >= 0 && dCol < width && dCol <= col + 1; ++dCol) {
                        char neighbor = map[dRow * width + dCol];
                        if (neighbor == '9') {
                            baby = new DragonHorde();
                            foundBaby = true;
                        } else if (neighbor == 'B') {
                            baby = new BarrierSuit();
                            foundBaby = true;
                        }

                        if (foundBaby) { // should for sure find a baby
                            // tile points to the dragon baby
                            unique_ptr<Item> item(baby);
                            theFloor[dRow][dCol]->moveItem(item);
                            // cur tile contains dragon
                            State babyPos {dCol, dRow};
                            unique_ptr<Enemy> dragon = make_unique<Dragon>(baby, babyPos);
                            cur->moveEnemy(dragon);
                            break;
                        }
                    }
                    if (foundBaby) break;
                }
                assert (foundBaby == true);
            } else if (getTileId(c) == TileType::MoveableTile) { // all other enemies
                enemyPosArr.emplace_back(State{col, row});
                EnemyFactory ef;
                EnemyType type;
                switch (c) {
                    case 'V':
                        type = EnemyType::Vampire;
                        break;
                    case 'W':
                        type = EnemyType::Werewolf;
                        break;
                    case 'T':
                        type = EnemyType::Troll;
                        break;
                    case 'N':
                        type = EnemyType::Goblin;
                        break;
                    case 'M':
                        type = EnemyType::Merchant;
                        break;
                    case 'X':
                        type = EnemyType::Phoenix;
                        break;
                    default:
                        cout << "what is " << c << endl;
                        break;
                }
                unique_ptr<Enemy> e = ef.initializeEnemy(type);
                cur->moveEnemy(e);
            }
        }
    }
    Random r;
    int idx = r.randomNum(enemyPosArr.size());
    State compass = enemyPosArr[idx];
    assert (getTile(compass)->hasEnemy() == true);
    getTile(compass)->getEnemy()->setCompass(true);
}

// reads in a string map and sets "theFloor" tile IDs
void Floor::init(string map, bool hasLayout) {
    // generate the actual floor & tiles
    for (int row = 0; row < height; row++) {
        vector<unique_ptr<Tile>> tmp;
        for (int col = 0; col < width; col++) {
            char c = map[row * width + col];
            tmp.emplace_back(make_unique<Tile>(col, row, getTileId(c)));
        }
        theFloor.emplace_back(move(tmp));
    }

    if (!hasLayout) {
        spawn();
    } else {
        layout(map);
    }
}

void Floor::generateBarrierSuit() {
    int itemIdx;
    int dragonIdx;
    Random r;
    while (true) {
        itemIdx = r.randomStrIdx(*this);
        dragonIdx = rNeighbourStrIdx(itemIdx,*this);
        if (dragonIdx != -1) break;
    }

    State babyPos = idxToPos(itemIdx);
    // cout << "BarrierSuit at " << babyPos.x << " " << babyPos.y << endl;

    DragonBaby *db = new BarrierSuit;
    Dragon *dragon = new Dragon{db, babyPos};
    unique_ptr<Item> item (db); // needs to take a pointer to a dragon
    unique_ptr<Enemy> enemy (dragon); // needs to take a pointer to a dragonBaby

    getTile(itemIdx)->moveItem(item);
    getTile(dragonIdx)->moveEnemy(enemy);
}

void Floor::print(string action) {
    for (auto &row : theFloor) {
        for (auto &col : row) {
            int curX = col->getState().x;
            int curY = col->getState().y;

            if (curX == pc->getState().x && curY == pc->getState().y) { // player
                cout << "\033[36m" << '@' << "\033[0m";
            } else if (curX == stairs.x && curY == stairs.y && pc->hasCompass()) { // stairs
                cout << "\033[44m" << '\\' << "\033[0m";
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
                    chambers.emplace_back(make_unique<Chamber>());
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

string intToStr(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

void Floor::updateFloor(string action) {
    for (auto &row : theFloor) {
        for (auto &tile : row) {

            // 1. if enemy, try to attack, if can't, then move
            if (tile->hasEnemy()) {
                unique_ptr<Enemy> &curEnemy = tile->getEnemy();
                if (curEnemy->isDead()) {
                    int goldReward = curEnemy->goldUponDead();
                    pc->addGold(goldReward);
                    action += "Earned " + intToStr(goldReward) + " gold from slaying " + curEnemy->getChar() + ". Another day another slay. ";
                    tile->removeEntities();
                    continue;
                } else if (curEnemy->hasMoved) {
                    continue;
                }

                State curPos = tile->getState();
                if (curEnemy->shouldAttack(curPos, pc->getState())) {
                    // cout << "Yes curEnemy->shouldAttack by: " << curEnemy->getChar() << endl;
                    action += curEnemy->getChar();
                    Random r;
                    if (r.randomNum(2) == 0) {
                        int damage = curEnemy->attack(*pc);
                        action += " deals " + intToStr(damage) + " damage to PC. ";
                        if (pc->isDead()) {
                            return;
                        }
                    } else {
                        action += " misses. ";
                    }
                } else {
                    if (curEnemy->isStationary()) continue; // dragons don't ever move
                    State newPos;
                    vector<int> neighbors = Random{}.randomArr(8);

                    for (int i = 0; i < (int)neighbors.size(); ++i) {
                        Direction dir = Direction(neighbors[i]);
                        newPos = getCoords(curPos, dir);
                        if (isValidMove(newPos)) break; // valid move found!
                        if (i == (int)neighbors.size() - 1) newPos = curPos; // checked all, none available, don't move
                    }

                    assert (0 <= newPos.y && newPos.y < height);
                    assert (0 <= newPos.x && newPos.x < width);

                    curEnemy->toggleMove(); // set hasMoved to true
                    Tile *newTile = theFloor[newPos.y][newPos.x].get();

                    assert (newTile->getType() == TileType::MoveableTile);
                    newTile->moveEnemy(curEnemy);
                }
            }

        }
    }
    // reset hasMoved boolean
    for (auto &row : theFloor) {
        for (auto &tile : row) {
            if (tile->hasEnemy() && tile->getEnemy()->hasMoved) tile->getEnemy()->toggleMove();
        }
    }
    print(action);
}

bool Floor::isValidMove(State &pos) {
    Tile *t = theFloor[pos.y][pos.x].get();
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
    Tile *t = theFloor[pos.y][pos.x].get();
    TileType type = t->getType();

    if (type == TileType::Empty || type == TileType::VWall || type == TileType::HWall) {
        return 0;
    } else if (type == TileType::MoveableTile) {
        if (t->hasEnemy()) return -1;
        if (t->hasItem()) {
            if (t->hasGold() && t->getItem()->validUse()) {
                cout << "player stepping on gold" << endl;
                pc->useItem(t->getItem().get());
                t->removeEntities();
                return 1;
            }
            return -1; // has a potion or barrierSuit
        }
    } else if (pos.x == stairs.x && pos.y == stairs.y) {
        // STAIRS
    }
    return 1; // must be valid Passage, Door, MoveableTile 
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
    return theFloor[pos.y][pos.x].get();
}

Tile *Floor::getTile(State pos) {
    return theFloor[pos.y][pos.x].get();
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

int Floor::rNeighbourStrIdx(int strIdx) {
    return rNeighbourStrIdx(strIdx, *this);
}

bool Floor::onStairs() {
    State pos = pc->getState();
    return stairs.x == pos.x && stairs.y == pos.y;
}
