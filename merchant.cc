#include "merchant.h"
#include "info.h"

using namespace std;

Merchant::Merchant() {
    init(unique_ptr<Info> (new Info {30, 70, 5, 0}));
    // instead of adding 1 gold immediately to player, Merchant drops gold
    id = EnemyType::Merchant;
    // still need to implement static hostile variable
}

Merchant::~Merchant() {}
