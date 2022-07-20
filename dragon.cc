#include "dragon.h"
#include "enemy.h"
#include "info.h"

using namespace std;

Dragon::Dragon() {
    init(unique_ptr<Info> (new Info {150, 20, 20, 0})); // initializes the stats?
    id = EnemyType::Dragon;
}


// we have to initialize it by calling the character and enemy component

// effect{new Info {0, 0 , 0, 0}}
/* const int atk = 20; // human default
    const int def = 20; // human defualt
    Info *stats; */

