#include "dragon.h"
#include "info.h"

using namespace std;

Dragon::Dragon() {
    init(unique_ptr<Info> (new Info {150, 20, 20, 0}));
    id = EnemyType::Dragon;
}

Dragon::~Dragon() {}

char Dragon::getChar() { return 'D'; }
