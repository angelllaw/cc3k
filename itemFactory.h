#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

class Floor;

class ItemFactory {
    Floor *floor;
    // UML ALSO HAS:
    // - maxItems : int
    // - itemList : string
    // what do those do?
    
    public:
    ItemFactory(Floor* floor); // this randomly generates the items and changes floor (adds directly)
    void generatePotions();
    void generateTreasures();
    void generateCompass();
};

#endif
