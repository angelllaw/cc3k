#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "item.h"

class Consumable : public Item {
    Info *effect;

    public:
    Consumable(ItemType i);
};

#endif
