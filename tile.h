#ifndef TILE_H
#define TILE_H

class Tile {

        int id = 0; // 0 should mean empty tile

    public:
        void setId(int newId);
        friend std::ostream &operator<<(std::ostream &out, const Tile &td);

};

#endif