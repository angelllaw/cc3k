#include "phoenix.h"
#include "info.h"

using namespace std;

Phoenix::Phoenix() {
    init(unique_ptr<Info> (new Info {50, 35, 20, 1}));
    id = EnemyType::Phoenix;
}

Phoenix::~Phoenix() {}
