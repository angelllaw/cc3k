#include "chamber.h"

void Chamber::addTile(int idx) {
    tiles.emplace_back(idx);
}