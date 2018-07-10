#ifndef _PLAYER_H_
#define _PLAYER_H_

class Board; 
class Invalid{};
class Check{};
class Player {
protected:
    Board *pb;
    int color;
    char ck = 'e';
    int ik;
    bool bishopValid(Board *p, char c1, int n1, char c2, int n2);
    bool rookValid(Board *p, char c1, int n1, char c2, int n2);
    bool knightValid(Board *p, char c1, int n1, char c2, int n2);
    int kingValid(Board *p, char c1, int n1, char c2, int n2);
    bool pawnValid(Board *p, char c1, int n1, char c2, int n2);
    bool valid(Board *p, char c1, int n1, char c2, int n2);
    void validmove(Board *p, char c1, int n1, char c2, int n2, char c);
    int findcok();
public: 
    Player(Board *pb, int i);
    bool isCheck();
    bool canMove();
    void setK(char c, int i);
    virtual void move() = 0;
    ~Player();
};
#endif
