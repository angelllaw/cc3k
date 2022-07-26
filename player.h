#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <memory>
#include <string>

class Item;

class Player : public Character {
    protected:
        std::unique_ptr<const Info> defaultStats;
        
        std::unique_ptr<State> pos;
        bool hasBarrierSuit = false;
        bool compass = false;

        int getAttacked(int damage) override; 

        Player(int hp, int atk, int def);

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

        void reset();
        virtual int getScore();
};

#endif
