#ifndef BARRIERSUIT_H
#define BARRIERSUIT_H

#include "dragonBaby.h"

class Human;
class Elf;
class Dwarf;
class Orc;

class BarrierSuit : public DragonBaby {

    public:
    void useOn(Human *p) override;
    void useOn(Elf *p) override; 
    void useOn(Dwarf *p) override; 
    void useOn(Orc *p) override;
};

#endif
