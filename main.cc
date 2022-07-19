#include <iostream>
#include <fstream>
#include "floor.h"
#include "item.h"
#include "enemy.h"
using namespace std;

int main (int argc, char *argv[]) {
    const int width = 79; // 79
    const int height = 25; // 25


    Floor f{width, height};
    f.print();

    if (argc == 2) { // optional cmd line arg

    } else {

    }
}
