#ifndef ITEM_H
#define ITEM_H

#include <string>

// notes:
// - dragons should be spawned when dragon hoards are spawned (1/8 prob.)
// - merchant hoards are implicitly there when merchants are spawned (1/9 prob.)
//      - no item (merchant hoard) actually appears until the merchant is dead

struct Info;
class Human;
class Elf;
class Dwarf;
class Orc;

enum class ItemType { RH, BA, BD, PH, WA, WD, NormalGold, SmallHorde, MerchantHorde, DragonHorde };

class Item {

    public:
    virtual void useOn(Human *p) = 0;
    virtual void useOn(Elf *p) = 0; 
    virtual void useOn(Dwarf *p) = 0; 
    virtual void useOn(Orc *p) = 0;
    virtual bool validUse();
    virtual bool isGold();
    virtual ~Item();
    virtual char getChar() = 0;

    virtual std::string getPotion();
};

#endif
