#ifndef GOBLIN_H
#define GOBLIN_H

#include "enemy.h"

class Goblin : public Enemy {
    
    public:
    Goblin();
    ~Goblin() override;

    char getChar() override;
};

#endif
