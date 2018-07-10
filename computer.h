#ifndef _computer_H_
#define _computer_H_
#include "player.h"

class LevelFour: public Player {
public:
    LevelFour(Board *pb, int i);
    void move() override;
    ~LevelFour();
};

class Level: public Player {
public:
    Level(Board *pb, int i);
    void move() override;
    ~Level();
};
#endif
