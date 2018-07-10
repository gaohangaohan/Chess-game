#ifndef _BOARD_H_
#define _BOARD_H_
#include <iostream>
#include <vector>
#include <memory>
#include "piece.h"

class Piece;
class Textdisplay;
class Graphicsdisplay;
class Board{
    bool ep = false;
    char epchar;
    int epint;
    Graphicsdisplay *gd = nullptr;
    std::vector<std::vector<bool>> am = 
        std::vector<std::vector<bool>>(8, std::vector<bool>(8, false));
    void BishopAttack(int x, int y);
    void RookAttack(int x, int y);
    void PawnAttack(int owner, int x, int y);
    void KnightAttack(int x, int y);
    void KingAttack(int x, int y);
    void SetFalse();
public:
    std::vector<Piece> vb;
    void init(int i = 1);
    void setdisplay(Graphicsdisplay *p);
    void setPiece(char type, char c, int i, int turn);
    void removePiece(char c, int i);
    void setEP(bool b, char c, int i);
    bool getEP();
    char getEPCHAR();
    int getEPINT();
    bool isAttacked(int owner, char c, int i);
    
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};
#endif
