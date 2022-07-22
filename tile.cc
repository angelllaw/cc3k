#include "tile.h"
#include "item.h"
#include "enemy.h"
#include "state.h"
#include <iostream>
#include <memory>

#include <cassert>

using namespace std;

Tile::Tile(int x, int y, TileType type) : pos{make_unique<State>(State{x, y})}, type{type} {}

Tile::~Tile() {}

void Tile::removeEntities() {
    // need to check if enemy is holding the compass
    // if the enemy is holding the compass when it dies, item should now point to compass
    // enemy should have a pointer to compass
    item.reset(nullptr); // deletes item and sets item to nullptr
    enemy.reset(nullptr); // delete enemy
}

void Tile::setId(TileType type) {
    this->type = type;
}

TileType Tile::getType() {
    return type;
}

bool Tile::hasEnemy() {
    return (type == TileType::MoveableTile) && (enemy.get() != nullptr);
}

bool Tile::hasItem() {
    return (type == TileType::MoveableTile) && (item.get() != nullptr);
}

unique_ptr<Enemy> &Tile::getEnemy() {
    return enemy;
}

unique_ptr<Item> &Tile::getItem() {
    return item;
}

State Tile::getState() {
    return *pos;
}

void Tile::moveEnemy(unique_ptr<Enemy> &other) {
    assert (enemy.get() == nullptr); // DELETE
    assert (other.get() != nullptr); 
    // what is currently at enemy is delete
    // but it should be okay since enemy should b nullptr
    enemy = move(other);
    // other.enemy is set to nullptr
    assert (other.get() == nullptr); // DELETE
}

void Tile::moveItem(unique_ptr<Item> &other) {
    assert (item.get() == nullptr);
    assert (other.get() != nullptr);
    item = move(other);
    assert (other.get() == nullptr);
}

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
                out << td.enemy->getChar();
            } else {
                out << td.item->getChar();
            }
            break;
    }
    return out;
}

