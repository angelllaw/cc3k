#ifndef ORC_H
#define ORC_H

#include "player.h"

class Orc : public Player {
    public:
    Orc();
    ~Orc() override;
    void useItem(Item *i) override;
    std::string printRace() override;
};

#endif
