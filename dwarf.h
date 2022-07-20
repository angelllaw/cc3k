#ifndef DWARF_H
#define DWARF_H

#include "player.h"

class Dwarf : public Player {
    public:
    Dwarf();
    ~Dwarf() override;
    void useItem(Item *i) override;
};

#endif
