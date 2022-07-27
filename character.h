#ifndef CHARACTER_H
#define CHARACTER_H
#include <memory>

struct Info;
struct State;

enum class Direction;

class Character {
    protected:
    std::unique_ptr<Info> stats;


    virtual int getAttacked(int damage) = 0; 

    public:
        Info &getInfo();
        void setHp(int newHp);
        void setAtk(int newAtk);
        void setDef(int newDef);
        void setGold(int newGold);

        bool isDead();

        virtual int attack(Character &victim);

       virtual ~Character();
};

#endif
