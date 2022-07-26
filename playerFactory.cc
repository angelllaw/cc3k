#include "playerFactory.h"
#include "player.h"
#include <memory>

#include "human.h"
#include "elf.h"
#include "dwarf.h"
#include "orc.h"

using namespace std;

shared_ptr<Player> PlayerFactory::generatePlayer(char race) {
    if (race == 'o') {
        return make_shared<Orc>();
    } else if (race == 'e') {
        return make_shared<Elf>();
    } else if (race == 'd') {
        return make_shared<Dwarf>();
    } else {
        return make_shared<Human>();
    }
}
