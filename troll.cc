#include "troll.h"
#include "info.h"

using namespace std;

Troll::Troll() {
    init(unique_ptr<Info> (new Info {70, 5, 10, 1}));
    id = EnemyType::Troll;
}

Troll::~Troll() {}
