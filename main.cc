#include <iostream>
#include <fstream>
#include <iomanip>
#include <memory>
#include "floor.h"
#include "item.h"
#include "enemy.h"
#include "player.h"
#include "human.h"
#include "state.h"
using namespace std;


int main (int argc, char *argv[]) {

    shared_ptr<Player> pc(nullptr); // warning: cannot access any fields here until you ctor a player 

    char cmd;
    bool validRace = false;

    while (cin >> cmd) {
        switch(cmd) {
            case 'h':
                pc = make_shared<Human>();
                cout << "made human" << endl;
                validRace = true;
                break;
            case 'e':
                validRace = true;
                break;
            case 'd':
                validRace = true;
                break;
            case 'o':
                validRace = true;
                break;
            default:
                cout << "Enter a valid race." << endl;
                break;
        }
        if (validRace) break;
    }

    if (!validRace) return 1;

    pc->setState(State{7, 5}); 
    
    Floor f{pc};

    
    

    if (argc == 2) { // optional cmd line arg

    } else {

    }

    

    f.printFloor();
    f.printMessage();

    f.updateFloor();
    f.printFloor();
}
