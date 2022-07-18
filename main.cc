#include <iostream>
#include <fstream>
#include "floor.h"
#include "item.h"
#include "enemy.h"
using namespace std;

int main (int argc, char *argv[]) {
    const int width = 47; // 79
    const int height = 10; // 25


    Floor f{width, height};
    f.print();

    f.testSetChambers(); // delete

    if (argc == 2) { // optional cmd line arg

    } else {

    }
}
