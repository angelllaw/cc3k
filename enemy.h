#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

enum class EnemyType { Dragon, Vampire, Werewolf, Troll, Goblin, Merchant, Phoenix };

class Enemy : public Character {
    protected:
    EnemyType id;

    public:
    void getAttacked(int damage) override;
    virtual ~Enemy();

    friend std::ostream &operator<<(std::ostream &out, const Enemy &e);
};

#endif
