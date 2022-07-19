#ifndef RANDOM_H
#define RANDOM_H

#include <vector>

class Random {
    public:
        int randomNum(int bottom, int top);
        int randomNum(int top);
        std::vector<int> randomArr(int top);
};

#endif
