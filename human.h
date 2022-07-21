#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class Human : public Player {
    public:
    Human();
    ~Human() override;
    void useItem(Item *i) override;
};

#endif
