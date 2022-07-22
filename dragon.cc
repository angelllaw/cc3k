#include "dragon.h"
#include "info.h"

using namespace std;

Dragon::Dragon() : baby{nullptr} {
    init(unique_ptr<Info> (new Info {150, 20, 20, 0}));
    id = EnemyType::Dragon;
}

Dragon::~Dragon() {}

void Dragon::setDragonBaby(DragonBaby *baby) {
    this->baby = baby;
}

char Dragon::getChar() { return 'D'; }
