#ifndef ELF_H
#define ELF_H

#include "player.h"

class Elf : public Player {
    public:
    Elf();
    ~Elf() override;
    void useItem(Item *i) override;
};

#endif
