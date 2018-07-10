#ifndef _PIECE_H_
#define _PIECE_H_

class Piece{
    char type;
    bool move;
    int owner;
public:
    Piece(char c, bool b, int i);
    char getType() const;
    bool nevermove() const;
    int getOwner() const;
};
#endif
