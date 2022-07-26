#include "goblin.h"
#include "info.h"

using namespace std;

Goblin::Goblin() {
    stats = make_unique<Info>(Info{70, 5, 10, 1});
}

Goblin::~Goblin() {}

char Goblin::getChar() { return 'N'; }
