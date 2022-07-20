#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H


class ItemFactory {
    // UML ALSO HAS:
    // - maxItems : int
    // - itemList : string
    // what do those do?
    
    public:
    // ItemFactory(); // this randomly generates the items and changes floor (adds directly)
    void generatePotions(Floor &floor);
    void generateTreasures(Floor &floor);
};

#endif
