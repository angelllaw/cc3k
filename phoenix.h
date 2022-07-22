#ifndef PHOENIX_H
#define PHOENIX_H

#include "enemy.h"

class Phoenix : public Enemy {
    
    public:
    Phoenix();
    ~Phoenix();

    char getChar() override;
};

#endif
