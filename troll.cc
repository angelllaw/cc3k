#include "troll.h"
#include "info.h"

using namespace std;

Troll::Troll() {
    stats = make_unique<Info>(Info{70, 5, 10, 1});
}

Troll::~Troll() {}

char Troll::getChar() { return 'T'; }
