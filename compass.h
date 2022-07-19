#ifndef COMPASS_H
#define COMPASS_H

#include "item.h"

class Compass : public Item {

    public:
    Compass();
    void useOn(Human* p);
    void useOn(Elf* p);
    void useOn(Dwarf* p);
    void useOn(Orc* p);
};

#endif
