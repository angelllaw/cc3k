#ifndef DRAGONBABY_H
#define DRAGONBABY_H

#include "item.h"
#include <memory>


class DragonBaby : public Item {

    public:
    // no need for DragonBaby to override the useOn functions since there will be no DragonBaby object (it's abstract)
    virtual ~DragonBaby();
};

#endif
