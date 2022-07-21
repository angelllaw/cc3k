#ifndef MERCHANT_H
#define MERCHANT_H

#include "enemy.h"

class Merchant : public Enemy {

    static bool hostile;

    public:
    Merchant();
    ~Merchant();

    bool shouldAttack(State &myPos, State &otherPos) override;
    void getAttacked(int damage) override;
    // void attack(Character &victim) override;
};

#endif
