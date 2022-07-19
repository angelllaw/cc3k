#include "chamber.h"

#include <cassert>

void Chamber::addTile(int idx) {
    tiles.emplace_back(idx);
}

int Chamber::getSize() { // this might cause errors: converting size_t to int implicitly
    return tiles.size();
}

int Chamber::getStrIdx(int i) { // this might cause errors: converting size_t to int implicitly
    assert (0 <= i && i < tiles.size());
    return tiles[i];
}
