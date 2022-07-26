#include "werewolf.h"
#include "info.h"

using namespace std;

Werewolf::Werewolf() {
    stats = make_unique<Info>(Info{120, 30, 5, 1});
}

Werewolf::~Werewolf() {}

char Werewolf::getChar() { return 'W'; }
