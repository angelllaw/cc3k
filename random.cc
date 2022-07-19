#include "random.h"
#include "floor.h"

#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// This is an extremely expensive and dumb way of generating random numbers
// This works well for returning a random element in an Array
//    - for returning a tile in a Chamber array..
//    - for returning a direction in a direction Enum
//    - for returning a chamber in a floor array of chambers
int Random::randomNum(int bottom, int top) {
    vector<int> v;
    for (int i = bottom; i < top; i++) { v.push_back(i); }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    return v[0];
}

int Random::randomNum(int top) {
    vector<int> v;
    for (int i = 0; i < top; i++) { v.push_back(i); }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    return v[0];
}

int Random::randomStrIdx(Floor *floor) {
    while (true) {
        int cIdx = randomNum(5); // random chamber
        int sizeOfChamber = floor->getChamberSize(cIdx);
        int tileIdx = randomNum(sizeOfChamber); // random tile in chamber
        int stringIdx = floor->getStringIdx(cIdx, tileIdx); // get string index of a specific tile

        if (floor->isValidMove(stringIdx)) return stringIdx;
    }
}

vector<int> Random::randomArr(int top) {
    vector<int> v;
    for (int i = 0; i < top; i++) { v.push_back(i); }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    return v;
}
