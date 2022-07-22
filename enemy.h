#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "compass.h"

enum class EnemyType { Dragon, Vampire, Werewolf, Troll, Goblin, Merchant, Phoenix };

class Enemy : public Character {
    protected:
    std::unique_ptr<Compass> c;

    public:
    int getAttacked(int damage) override;
    virtual bool shouldAttack(State &myPos, State &otherPos);
    virtual ~Enemy();
    virtual void toggleMove();
    bool hasMoved = false;
    bool hasCompass();
    void setCompass(std::unique_ptr<Compass> &c);
    std::unique_ptr<Compass>& getCompass();

    virtual char getChar() = 0;

    friend std::ostream &operator<<(std::ostream &out, const Enemy &e);
};

#endif
