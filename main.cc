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
#include "playerFactory.h"
#include "direction.h"
#include "state.h"
#include "info.h"
#include "random.h"
#include "merchant.h"
using namespace std;

Direction getDirection();
string directionString(Direction dir);
void printGoodBye();
bool attemptMove(Floor &f, shared_ptr<Player> pc, Direction dir, string &action);
string numToStr(int num);

int main (int argc, char *argv[]) {

    bool restart;

    do {
        restart = false;

        Merchant::reset();

        const int width = 79;
        const int height = 25;

        cout << endl << endl << "GAME START" << endl << endl;
        cout << "Select your player's race." << endl;
        cout << "h — for human" << endl;
        cout << "e — for elf" << endl;
        cout << "d — for dwarf" << endl;
        cout << "o — for orc" << endl;
        cout << endl << "Enter to select:" << endl;
    
        shared_ptr<Player> pc(nullptr);

        // 1. Choose Player Race
        char cmd;
        bool validRace = false;

        while (cin >> cmd) {
            PlayerFactory pf;
            switch(cmd) {
                case 'h':
                    cout << "You have selected Human." << endl;
                    validRace = true;
                    break;
                case 'e':
                    cout << "You have selected Elf." << endl;
                    validRace = true;
                    break;
                case 'd':
                    cout << "You have selected Dwarf." << endl;
                    validRace = true;
                    break;
                case 'o':
                    cout << "You have selected Orc." << endl;
                    validRace = true;
                    break;
                default:
                    cout << "Invalid command. Enter a valid race:" << endl;
                    break;
            }
            if (validRace) {
                pc = pf.generatePlayer(cmd);
                break;
            }
        }

        if (cin.fail()) break; 

        ifstream floorFile;
        ifstream numFile;

        bool hasArg = false;

        // opening map txt file
        if (argc == 2) { // optional cmd line arg
            floorFile.open(argv[1]);
            hasArg = true;
        } else {
            floorFile.open("defaultMap.txt");
        }
        numFile.open("defaultNumMap.txt");

        Random r;
        int barrierSuitFloor = r.randomNum(5);
        // barrierSuitFloor = 0; // remove later (for testing rn)
        
        int floorNum = 0;

        for (; floorNum < 5; ++floorNum) {
            string floorMap;
            string numMap;
            string line;

            if (!hasArg) {
                floorFile.clear();
                floorFile.seekg(ios::beg);
                // rereads defaultmap if no cmd line arg
            }
            numFile.clear();
            numFile.seekg(ios::beg); // rereads numMap for every new floor

            // gets one floor
            for (int i = 0; i < height; ++i) {
                getline(floorFile, line);
                floorMap += line;

                getline(numFile, line);
                numMap += line;
            }

            Floor f{pc, numMap, floorMap, hasArg, floorNum + 1};
            
            // call floor to generate a barrier suit
            if (!hasArg && floorNum == barrierSuitFloor) {
                f.generateBarrierSuit();
            }
            
            string action = "Action: ";
            action += "Player character has spawned.";
            f.print(action);

            while (cin >> cmd) {
                action = "Action: ";
                Direction dir;
                switch(cmd) {
                    // MOVE
                    case 'n':
                        cin >> cmd;
                        if (cmd == 'o') dir = Direction::N;
                        if (cmd == 'e') dir = Direction::NE;
                        if (cmd == 'w') dir = Direction::NW;

                        if (!attemptMove(f, pc, dir, action)) continue;
                        break;

                    case 'e':
                        cin >> cmd;
                        if (cmd == 'a') dir = Direction::E;
                        if (!attemptMove(f, pc, dir, action)) continue;
                        break;
                    case 's':
                        cin >> cmd;
                        if (cmd == 'o') dir = Direction::S;
                        if (cmd == 'e') dir = Direction::SE;
                        if (cmd == 'w') dir = Direction::SW;

                        if (!attemptMove(f, pc, dir, action)) continue;
                        break;
                    case 'w':
                        cin >> cmd;
                        if (cmd == 'e') dir = Direction::W;
 
                        if (!attemptMove(f, pc, dir, action)) continue;
                        break;
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
                            } else if (f.getTile(itemLoc)->getItem()->validUse() == false) {
                                // only for dragon babys
                                continue;
                            }
                            // There is a valid item to use
                            if (f.getTile(itemLoc)->getItem()->getChar() == 'C') {
                                action += "PC uses Compass. Stairs Appear. ";
                            } else if (f.getTile(itemLoc)->getItem()->getChar() == 'B') {
                                action += "PC equips Barrier Suit. ";
                            } else {
                                action += "PC uses " + f.getTile(itemLoc)->getItem()->getPotion() + ". ";
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
                                action += "PC deals " + numToStr(damage) + " damage to ";
                                action += t->getEnemy()->getChar();

                                int hp = t->getEnemy()->getInfo().hp;
                                action += " (" + numToStr(hp)  + " HP). ";
                            } else {
                                action += "PC attacks nothing. ";
                            }
                            break;
                        }
                    case 'r':
                        restart = true;
                        break;
                    case 'q':
                        // destroy stuff?
                        printGoodBye();
                        return 0;
                        break;
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
                if (restart || pc->isDead()) break;
                f.updateFloor(action); // print is called inside here
                if (pc->isDead()) break;
            }
            if (cin.fail() || pc->isDead() || restart) {
                break;
            }
        }
        if (floorNum == 5) {
            cout << "Congratulations! You beat the dungeon. Have a cookie." << endl;
            cout << "Score: " << pc->getScore() << endl;
        } else if (pc->isDead()) {
            cout << "You died!" << endl;
            cout << "Score: " << pc->getScore() << endl;
            cout << "Do you want to restart? [Y/N]." << endl;
            cin >> cmd;
            restart = (cmd == 'Y' || cmd == 'y' ? true : false);
        }
    } while (restart);
    printGoodBye();
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

void printGoodBye() {
    cout << "Thanks for playing CC3K+" << endl;
    cout << "made by Olivia and Angela" << endl;
}

bool attemptMove(Floor &f, shared_ptr<Player> pc, Direction dir, string &action) {
    State nextPos = f.getState(pc->getState(), dir);
    if (f.validPlayerTile(nextPos) == 1) {
        pc->move(dir);
        action += "PC moves " + directionString(dir);
        f.checkSurroundings(action);
        return true;
    } else {
        cout << "Invalid Move." << endl;
        return false;
    }
}

string numToStr(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}
