#ifndef _LevelTT_H
#define _LevelTT_H
#include "player.h"

class LevelTwo: public Player {
public:
    LevelTwo(Board *pb, int i);
    void move() override;
    ~LevelTwo();
};

class LevelThree: public Player {
public:
    LevelThree(Board *pb, int i);
    void move() override;
    ~LevelThree();
};
#endif
