#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character {
   protected:
    bool compass = false;

   public:
    bool hasMoved = false;

    int getAttacked(int damage) override;
    virtual bool shouldAttack(State &myPos, State &otherPos);
    virtual ~Enemy();
    void toggleMove();
    bool hasCompass();
    void setCompass(bool status);
    virtual int goldUponDead();
    virtual bool dropsMerchantHorde();
    virtual bool isStationary();
    virtual bool isHostile();

    virtual char getChar() = 0;

    friend std::ostream &operator<<(std::ostream &out, const Enemy &e);
};

#endif
