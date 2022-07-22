#include "goblin.h"
#include "info.h"

using namespace std;

Goblin::Goblin() {
    init(unique_ptr<Info> (new Info {70, 5, 10, 1}));
    id = EnemyType::Goblin;
}

Goblin::~Goblin() {}

char Goblin::getChar() { return 'N'; }
