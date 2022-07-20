#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <memory>

enum class Race{ Human, Dwarf, Elf, Orc };

class Player : public Character {
    protected:
        const int atk = 20; // human default
        const int def = 20; // human defualt
        
        Race race;
        std::unique_ptr<State> pos;
        bool hasBarrierSuit = false;
        bool compass = false;

        

        void getAttacked(int damage) override; 

        Player(Race race, Info stats);

    public:
        State &getState();
        void setState(State newPos);
        Race getRace();
        void setBarrierSuitTrue();
        void setCompassTrue();
        bool hasCompass();
        void addGold(int amount);
        ~Player();
};

#endif
