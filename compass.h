#ifndef COMPASS_H
#define COMPASS_H

#include "item.h"

class Compass : public Item {

    public:
    void useOn(Human* p);
    void useOn(Elf* p);
    void useOn(Dwarf* p);
    void useOn(Orc* p);
    char getChar() override;
    ~Compass();
};

#endif
