#ifndef INFO_H
#define INFO_H

struct Info {
    int hp;
    int atk;
    int def;
    int gold;
    void add(const Info toAdd);
};

#endif
