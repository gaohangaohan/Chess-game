#ifndef _Human_H_
#define _Human_H_
#include "player.h"

class Human: public Player{
public:
    Human(Board *pb, int i);
    void move() override;
    ~Human();
};

class LevelOne: public Player {
public:
    LevelOne(Board *pb, int i);
    void move() override;
    ~LevelOne();
};
#endif
