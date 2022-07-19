#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "item.h"

class Consumable : public Item {
    Info *effect;

    public:
    Consumable(ItemType i);
    void useOn(Human *p) override;
    void useOn(Elf *p) override; 
    void useOn(Dwarf *p) override; 
    void useOn(Orc *p) override; 
};

#endif
