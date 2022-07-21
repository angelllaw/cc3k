#include <iostream>
#include <fstream>
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

    // 2. Spawn Player
    pc->setState(State{7, 5}); 
    
    string action = "Action: ";

    Floor f{pc};
    action += "Player character has spawned.";
    f.print(action);
    // we need to randomly generate a spawn point for Player AFTER we initialize floor.
    // (this is because we have to make sure Player does not spawn on top of Stairs or an Item or Enemy)

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
                    f.removeItem(itemLoc);
                    action += "PC uses Potion";
                    break;
                }
            case 'a':
                {
                    // attack
                    action += "PC attacks";
                    break;
                }
            default:
                cout << "invalid cmd" << endl;
                continue;
        }
        f.updateFloor(action); // print is called inside here
    }
    

    if (argc == 2) { // optional cmd line arg

    } else {

    }

}