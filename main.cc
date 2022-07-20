#include <iostream>
#include <fstream>
#include <iomanip>
#include <memory>
#include "floor.h"
#include "item.h"
#include "enemy.h"
#include "player.h"
#include "human.h"
using namespace std;


int main (int argc, char *argv[]) {

    shared_ptr<Player> pc = make_shared<Human>();


    Floor f{pc};
    

    if (argc == 2) { // optional cmd line arg

    } else {

    }

    f.printFloor();
    f.printMessage();
}
