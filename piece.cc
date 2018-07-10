#include "piece.h"

Piece::Piece(char c, bool b, int i): type{c}, move{b}, owner{i} {}
char Piece::getType() const {return this->type;}
bool Piece::nevermove() const {return !this->move;}
int Piece::getOwner() const {return this->owner;}
