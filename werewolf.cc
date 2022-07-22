#include "werewolf.h"
#include "info.h"

using namespace std;

Werewolf::Werewolf() {
    init(unique_ptr<Info> (new Info {120, 30, 5, 1}));
    id = EnemyType::Werewolf;
}

Werewolf::~Werewolf() {}

char Werewolf::getChar() { return 'W'; }
