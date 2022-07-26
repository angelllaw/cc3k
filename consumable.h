#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "item.h"
#include <memory>
#include <string>
#include "info.h"

class Consumable : public Item {
    std::unique_ptr<Info> effect;

    public:
    Consumable(ItemType i);
    void useOn(Human *p) override;
    void useOn(Elf *p) override; 
    void useOn(Dwarf *p) override; 
    void useOn(Orc *p) override; 
    char getChar() override;
    bool isGold() override;
    std::string getPotion() override;
};

#endif
