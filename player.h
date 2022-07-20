#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <memory>

enum class Race{ Human, Dwarf, Elf, Orc };

class Player : public Character {
    protected:
        const int atk = 20; // human default
        const int def = 20; // human defualt
        std::unique_ptr<State> pos;
        bool hasBarrierSuit = false;

        Race race;

        void getAttacked(int damage) override; 

        Player(Race race, Info stats);

    public:
        State &getState();
        void setState(State newPos);
        Race getRace();
        ~Player();
};

#endif
