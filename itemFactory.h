#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

class Floor;

class ItemFactory {
    
    public:
    void generatePotions(Floor &floor);
    void generateTreasures(Floor &floor);
};

#endif
