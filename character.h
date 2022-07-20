#ifndef CHARACTER_H
#define CHARACTER_H
#include <memory>

struct Info;
struct State;

enum class Direction;

class Character {
    protected:
    std::unique_ptr<Info> stats;


    virtual void getAttacked(int damage) = 0; 

    public:
        Info getInfo();
        void setHp(int newHp);
        void setAtk(int newAtk);
        void setDef(int newDef);
        void setGold(int newGold);

        
        /* State getState();
        void setState(State newPos); */

        bool isDead();
        void toggleMove();
        bool hasMoved = false;

        virtual void attack(Character &victim);
        virtual bool move(Direction dir);

        void init(std::unique_ptr<Info> infoToMove);

       //  virtual ~Character(); // causing issues with make for some reason

};

#endif
