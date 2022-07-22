#include "phoenix.h"
#include "info.h"

using namespace std;

Phoenix::Phoenix() {
    init(unique_ptr<Info> (new Info {50, 35, 20, 1}));
}

Phoenix::~Phoenix() {}

char Phoenix::getChar() { return 'X'; }
