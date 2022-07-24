#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <memory>
#include "floor.h"
#include "item.h"
#include "tile.h"
#include "enemy.h"
#include "player.h"
#include "human.h"
#include "elf.h"
#include "dwarf.h"
#include "orc.h"
#include "direction.h"
#include "state.h"
#include "info.h"
using namespace std;

Direction getDirection();

string directionString(Direction dir);

int main (int argc, char *argv[]) {

    const int width = 79;
    const int height = 25;

    cout << endl << endl << "GAME START" << endl << endl;
    cout << "Select your player's race." << endl;
    cout << "h — for human" << endl;
    cout << "e — for elf" << endl;
    cout << "d — for dwarf" << endl;
    cout << "o — for orc" << endl;
    cout << endl << "Enter to select:" << endl;
    
    shared_ptr<Player> pc(nullptr); // warning: cannot access any fields here until you ctor a player 

    // 1. Choose Player Race
    char cmd;
    bool validRace = false;

    while (cin >> cmd) {
        switch(cmd) {
            case 'h':
                pc = make_shared<Human>();
                cout << "You have selected Human." << endl;
                validRace = true;
                break;
            case 'e':
                pc = make_shared<Elf>();
                cout << "You have selected Elf." << endl;
                validRace = true;
                break;
            case 'd':
                pc = make_shared<Dwarf>();
                cout << "You have selected Dwarf." << endl;
                validRace = true;
                break;
            case 'o':
                pc = make_shared<Orc>();
                cout << "You have selected Orc." << endl;
                validRace = true;
                break;
            default:
                cout << "Invalid command. Enter a valid race:" << endl;
                break;
        }
        if (validRace) break;
    }

    ifstream floorFile;
    ifstream numFile;

    bool hasArg = false;

    if (argc == 2) { // optional cmd line arg
        floorFile.open(argv[1]);
        hasArg = true;
    } 

    for (int floorNum = 0; floorNum < 5; ++floorNum) {
        string floorMap;
        string numMap;
        string line;

        if (!hasArg) {
            floorFile.open("defaultMap.txt"); // reopens defaultmap if no cmd line arg
        }
        numFile.open("defaultNumMap.txt"); // reopens numMap for every new floor

        // gets one floor
        for (int i = 0; i < height; ++i) {
            getline(floorFile, line);
            floorMap += line;

            getline(numFile, line);
            numMap += line;
        }

        

        Floor f{pc, numMap, floorMap, hasArg};

        // 2. Spawn Player
        pc->setState(State{7, 5}); 
        
        
        string action = "Action: ";
        
        action += "Player character has spawned.";
        f.print(action);
        // we need to randomly generate a spawn point for Player AFTER we initialize floor.
        // (this is because we have to make sure Player does not spawn on top of Stairs or an Item or Enemy)

        // validate move, pick up gold by walking over it, recognize stairs
        while (cin >> cmd) {
            action = "Action: ";
            Direction dir;
            State nextPos;
            switch(cmd) {
                // MOVE
                case 'n':
                {   
                    cin >> cmd;
                    if (cmd == 'o') dir = Direction::N;
                    if (cmd == 'e') dir = Direction::NE;
                    if (cmd == 'w') dir = Direction::NW;
                    nextPos = f.getState(pc->getState(), dir);
                    if (f.validPlayerTile(nextPos) == 1) {
                        pc->move(dir);
                        action += "PC moves " + directionString(dir);
                    } else {
                        cout << "Invalid Move." << endl;
                        continue;
                    }
                    break;
                } 
                case 'e':
                {
                    cin >> cmd;
                    if (cmd == 'a') dir = Direction::E;
                    State nextPos = f.getState(pc->getState(), dir);
                    if (f.validPlayerTile(nextPos) == 1) {
                        pc->move(dir);
                        action += "PC moves " + directionString(dir);
                    } else {
                        cout << "Invalid Move." << endl;
                        continue;
                    }
                    break;
                }
                case 's':
                {
                    cin >> cmd;
                    if (cmd == 'o') dir = Direction::S;
                    if (cmd == 'e') dir = Direction::SE;
                    if (cmd == 'w') dir = Direction::SW;
                    nextPos = f.getState(pc->getState(), dir);
                    if (f.validPlayerTile(nextPos) == 1) {
                        pc->move(dir);
                        action += "PC moves " + directionString(dir);
                    } else {
                        cout << "Invalid Move." << endl;
                        continue;
                    }
                    break;
                }
                case 'w':
                {
                    cin >> cmd;
                    if (cmd == 'e') dir = Direction::W;
                    nextPos = f.getState(pc->getState(), dir);
                    if (f.validPlayerTile(nextPos) == 1) {
                        pc->move(dir);
                        action += "PC moves " + directionString(dir);
                    } else {
                        cout << "Invalid Move." << endl;
                        continue;
                    }
                    break;
                }
                // USE ITEM
                case 'u':
                    {
                        Direction d = getDirection(); // reads the next to chars from stdIn
                        State itemLoc = f.getState(pc->getState(), d);
                        if (f.getTile(itemLoc)->hasItem() == false) {
                            cout << "Invalid Cmd. No item to use." << endl;
                            continue;
                        } else if (f.getTile(itemLoc)->hasGold()) {
                            cout << "Invalid Cmd. Pick up Gold by walking over it." << endl;
                            continue;
                        }
                        // There is a valid item to use
                        if (f.getTile(itemLoc)->getItem()->getChar() == 'C') {
                            action += "PC uses Compass. Stairs Appear.";
                        } else {
                            action += "PC uses Potion";
                        }
                        pc->useItem(f.getItem(itemLoc));
                        f.removeItem(itemLoc);
                        break;
                    }
                // ATTACK
                case 'a':
                    {
                        Direction d = getDirection();
                        State enemyLoc = f.getState(pc->getState(), d);
                        Tile *t = f.getTile(enemyLoc);
                        if (t->hasEnemy()) {
                            int damage = pc->attack(*t->getEnemy()); // enemy is not null

                            stringstream ss;
                            ss << damage;
                            action += "PC deals " + ss.str() + " damage to ";
                            action += t->getEnemy()->getChar();

                            int hp = t->getEnemy()->getInfo().hp;
                            ss.str("");
                            ss << hp;
                            // cout << "HP:" << hp << endl;
                            action += " (" + ss.str() + " HP). ";
                        } else {
                            action += "PC attacks nothing. ";
                        }
                        break;
                    }
                default:
                    cout << "invalid cmd" << endl;
                    continue;
            }

            f.updateFloor(action); // print is called inside here
        }
    }
    

    
    


}

Direction getDirection() {
    char first;
    char second;
    cin >> first;
    cin >> second;

    switch(first) {
            case 'n':
                if (second == 'o') return Direction::N;
                if (second == 'e') return Direction::NE;
                if (second == 'w') return Direction::NW;
            case 'e':
                if (second == 'a') return Direction::E;
            case 's':
                if (second == 'o') return Direction::S;
                if (second == 'e') return Direction::SE;
                if (second == 'w') return Direction::SW;
            case 'w':
                if (second == 'e') return Direction::W;
            default:
                cout << "invalid direction" << endl;
    }
    return Direction::N;
}

// get direction string
string directionString(Direction dir) {
    switch(dir) {
        case Direction::N:     return "North";
        case Direction::NE:    return "North East";
        case Direction::E:     return "East";
        case Direction::SE:    return "South East";
        case Direction::S:     return "South";
        case Direction::SW:    return "South West";
        case Direction::W:     return "West";
        default:               return "North West";
    }
}
