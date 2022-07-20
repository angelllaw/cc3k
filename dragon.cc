#include "dragon.h"
#include "enemy.h"

Dragon::Dragon() {
    stats = new {150, 20, 20, 0}; // CHANGE TO UNIQUE POINTER
}

// we have to initialize it by calling the character and enemy component

// effect{new Info {0, 0 , 0, 0}}
/* const int atk = 20; // human default
    const int def = 20; // human defualt
    Info *stats; */

