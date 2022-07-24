#ifndef DRAGONHORDE_H
#define DRAGONHORDE_H

#include "dragonBaby.h"
#include "item.h" // get rid of, temporary

class Human;
class Elf;
class Dwarf;
class Orc;

class DragonHorde : public DragonBaby {
    int gold = 6;

    public:
    void useOn(Human *p) override;
    void useOn(Elf *p) override; 
    void useOn(Dwarf *p) override; 
    void useOn(Orc *p) override;
    char getChar() override;
    bool isGold() override;
};

#endif
