#ifndef MERCHANT_H
#define MERCHANT_H

#include "enemy.h"

class Merchant : public Enemy {

    static bool hostile;

    public:
    Merchant();
    ~Merchant();

    bool shouldAttack(State &myPos, State &otherPos) override;
    int getAttacked(int damage) override;
    bool dropsMerchantHorde() override;

    char getChar() override;
    bool isHostile() override;

    static void reset();
};

#endif
