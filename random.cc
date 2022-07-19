#include "random.h"

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

vector<int> Random::randomArr(int top) {
    vector<int> v;
    for (int i = 0; i < top; i++) { v.push_back(i); }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    return v;
}