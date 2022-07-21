#ifndef DRAGON_H
#define DRAGON_H

#include "enemy.h"

class Dragon : public Enemy {
    // still need to implement pointer to DragonBaby
    public:
    Dragon();
    ~Dragon();

    char getChar() override;
};

#endif
