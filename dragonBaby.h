#ifndef DRAGONBABY_H
#define DRAGONBABY_H

#include "item.h"
#include <memory>

class Dragon;

class DragonBaby : public Item {
    
    bool hasProtector = true;

    public:
    // no need for DragonBaby to override the useOn functions since there will be no DragonBaby object (it's abstract)
    // void setDragonMomma(Dragon *momma);
    virtual ~DragonBaby();
    bool hasNoProtector();
    void setProtector();
    bool validUse() override;
};

#endif
