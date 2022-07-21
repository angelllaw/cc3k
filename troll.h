#ifndef TROLL_H
#define TROLL_H

#include "enemy.h"

class Troll : public Enemy {
    
    public:
    Troll();
    ~Troll();

    char getChar() override;
};

#endif
