#ifndef INFO_H
#define INFO_H

struct Info {
    int hp;
    int atk;
    int def;
    int gold;
    void add(const Info toAdd);
};

/* 
I don't think overloading + is the way to go, we need to be able to know if 
Info operator+( const Info & info1, const Info & info2 ) {
    Info i { info1.hp + info2.hp, info1.atk + info2.atk, info1.def + info2.def, info1.gold + info2.gold};
    return i;
}
 */
#endif