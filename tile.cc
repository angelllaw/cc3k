#include "tile.h"
#include "item.h"
#include "enemy.h"
#include <iostream>
using namespace std;

Tile::Tile(int x, int y, TileType type) : x{x}, y{y}, type{type} {}

Tile::~Tile() {}

std::ostream &operator<<(std::ostream &out, const Tile &td) {
    TileType cur = td.type;
    switch (cur) {
        case TileType::Empty:
            out << ' ';
            break;
        case TileType::VWall:
            out << '|';
            break;
        case TileType::HWall:
            out << '-';
            break;
        case TileType::Passage:
            out << '#';
            break;
        case TileType::Door:
            out << '+';
            break;
         case TileType::MoveableTile:
            if (td.item.get() == nullptr && td.enemy.get() == nullptr) {
                out << '.';
            } else if (td.item.get() == nullptr) {
                out << 'E'; // HAVEN'T ADDED ENEMY IDENTIFYING ENUMS YET, update!
            } else {
                out << 'I'; // UPDATE with item enum later
            }
            break;
    }
    return out;
}
