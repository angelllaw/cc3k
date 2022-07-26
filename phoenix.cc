#include "phoenix.h"
#include "info.h"

using namespace std;

Phoenix::Phoenix() {
    stats = make_unique<Info>(Info{50, 35, 20, 1});
}

Phoenix::~Phoenix() {}

char Phoenix::getChar() { return 'X'; }
