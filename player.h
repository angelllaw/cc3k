#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <memory>
#include <string>

class Item;

class Player : public Character {
    protected:
        const int atk = 20; // human default
        const int def = 20; // human defualt
        
        std::unique_ptr<State> pos;
        bool hasBarrierSuit = false;
        bool compass = false;

        void getAttacked(int damage) override; 

        Player(const int atk, const int def);

    public:
        State &getState();
        void setState(State newPos);
        virtual std::string printRace() = 0;
        void setBarrierSuitTrue();
        void setCompassTrue();
        bool hasCompass();
        void addGold(int amount);
        virtual void useItem(Item *i) = 0;
        bool move(Direction dir) override;
        ~Player();
};

#endif
