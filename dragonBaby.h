#ifndef DRAGONBABY_H
#define DRAGONBABY_H

#include "item.h"

class Dragon;

class DragonBaby : public Item {
    
    bool hasProtector = true;

   public:
    virtual ~DragonBaby();
    bool hasNoProtector();
    void setProtector();
    bool validUse() override;
};

#endif
