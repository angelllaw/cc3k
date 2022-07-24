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
    numFile.open("defaultNumMap.txt");

    for (int floorNum = 0; floorNum < 5; ++floorNum) {
        string floorMap;
        string numMap;
        string line;

        if (!hasArg) {
            floorFile.clear();
            floorFile.open("defaultMap.txt");
            floorFile.seekg(ios::beg);
            // reopens defaultmap if no cmd line arg
        }
        numFile.clear();
        numFile.seekg(ios::beg); // reopens numMap for every new floor

        // gets one floor
        for (int i = 0; i < height; ++i) {
            getline(floorFile, line);
            floorMap += line;

            getline(numFile, line);
            numMap += line;
        }

        

        Floor f{pc, numMap, floorMap, hasArg};

        // 2. Spawn Player
        if (!hasArg) {
            cout << "random spawn" << endl;
            pc->setState(State{7, 5}); 
        }
        
        
        
        string action = "Action: ";
        
        action += "Player character has spawned.";
        f.print(action);
        // we need to randomly generate a spawn point for Player AFTER we initialize floor.
        // (this is because we have to make sure Player does not spawn on top of Stairs or an Item or Enemy)

        // validate move, pick up gold by walking over it, recognize stairs
        while (cin >> cmd) {
            action = "Action: ";
            switch(cmd) {
                // MOVE
                case 'n':
                    cin >> cmd;
                    if (cmd == 'o') {
                        pc->move(Direction::N);
                        action += "PC moves North";
                    }
                    if (cmd == 'e') {
                        pc->move(Direction::NE);
                        action += "PC moves Northeast";
                    }
                    if (cmd == 'w') {
                        pc->move(Direction::NW);
                        action += "PC moves Northwest";
                    }
                    break;
                case 'e':
                    cin >> cmd;
                    if (cmd == 'a') {
                        pc->move(Direction::E);
                        action += "PC moves East";
                    }
                    break;
                case 's':
                    cin >> cmd;
                    if (cmd == 'o') {
                        pc->move(Direction::S);
                        action += "PC moves South";
                    }
                    if (cmd == 'e') {
                        pc->move(Direction::SE);
                        action += "PC moves Southeast";
                    }
                    if (cmd == 'w') {
                        pc->move(Direction::SW);
                        action += "PC moves Southwest";
                    }
                    break;
                case 'w':
                    cin >> cmd;
                    if (cmd == 'e') {
                        pc->move(Direction::W);
                        action += "PC moves West";
                    }
                    break;
                // USE ITEM
                case 'u':
                    {
                        Direction d = getDirection(); // reads the next to chars from stdIn
                        State itemLoc = f.getState(pc->getState(), d);
                        Item *i = f.getItem(itemLoc);
                        pc->useItem(i); // before using the item, should do some kind of error checking to ensure
                        // we're not "using" a nullptr, that gives us seg fault
                        // what if we try to use a DragonHorde/barrierSuit but the Dragon is still guarding it?
                        // how do we know we didn't succesfully us it?
                        // what if removeItem checks if the item was valid to remove
                        f.removeItem(itemLoc);
                        action += "PC uses Potion"; // change this to work with compass
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

            // if player is on stairs
            if (f.onStairs()) {
                pc->reset();
                // floor shouldn't need to be reset since it is on the stack and has unique-ptr (auto delete)
                break;
            }

            f.updateFloor(action); // print is called inside here
        }
        if (cin.fail()) {
            break;
        }
    }
    cout << "You've reached the end" << endl;
}