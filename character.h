#ifndef CHARACTER_H
#define CHARACTER_H

struct Info;
struct State;

enum class Direction { N, NE, E, SE, S, SW, W, NW };

class Character {
    const int atk = 20; // human default
    const int def = 20; // human defualt
    Info *stats;
    State *pos;

    bool hasMoved = false;

    virtual void getAttacked(int damage) = 0; 

    public:
        Info getInfo();
        void setHp(int newHp);
        void setAtk(int newAtk);
        void setDef(int newDef);
        void setGold(int newGold);

        State getState();
        void setState(State newPos);

        bool isDead();
        void toggleMove();

        virtual void attack(Character &victim);
        virtual bool move(Direction dir);

        // virtual ~Character(); // causing issues with make for some reason

};

#endif
