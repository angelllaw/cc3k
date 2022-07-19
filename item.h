#ifndef ITEM_H
#define ITEM_H

// notes:
// - dragons should be spawned when dragon hoards are spawned (1/8 prob.)
// - merchant hoards are implicitly there when merchants are spawned (1/9 prob.)
//      - no item (merchant hoard) actually appears until the merchant is dead

struct Info;
class Human;
class Elf;
class Dwarf;
class Orc;

enum class ItemType { RH, BA, BD, PH, WA, WD, NormalGold, SmallHorde, MerchantHorde, DragonHorde, DragonBaby, Compass };

class Item {
    protected:
    ItemType id;

    public:
    virtual void useOn(Human *p);
    virtual void useOn(Elf *p); 
    virtual void useOn(Dwarf *p); 
    virtual void useOn(Orc *p); 
    // UML has getState (says item should know its coords, is this unnecessary?)
    virtual ~Item() = 0;
};

#endif
