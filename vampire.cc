#include "vampire.h"
#include "info.h"

using namespace std;

Vampire::Vampire() {
    init(unique_ptr<Info> (new Info {50, 25, 25, 1}));
}

Vampire::~Vampire() {}

char Vampire::getChar() { return 'V'; }
