#include "board.h"
#include "piece.h"
#include "graphicsdisplay.h"

void Board::init(int i) {
    if(i == 0) {
        for(int i = 0; i < 64; ++i) {
            vb.emplace_back(' ', false, -1);
        }
    } else {
        vb.clear();
        for (int i = 0; i < 8; ++i) {
            if (i == 0 || i == 7) {
                vb.emplace_back('R', false, 0);
            } else if (i == 1 || i == 6) {
                vb.emplace_back('N', false, 0);
            } else if (i == 2 || i == 5) {
                vb.emplace_back('B', false, 0);  
            } else if (i == 3) {
                vb.emplace_back('Q', false, 0);
            } else {
                vb.emplace_back('K', false, 0);
            }
        }
        for (int p = 0; p < 8; ++p) {vb.emplace_back('P', false, 0);}
        for (int q = 0; q < 32; ++q) {vb.emplace_back(' ', false, -1);}
        for (int k = 0; k < 8; ++k) {vb.emplace_back('P', false, 1);} 
        for (int j = 0; j < 8; ++j) {
            if (j == 0 || j == 7) {
                vb.emplace_back('R', false, 1);
            } else if (j == 1 || j == 6) {
                vb.emplace_back('N', false, 1);
            } else if (j == 2 || j == 5) {
                vb.emplace_back('B', false, 1); 
            } else if (j == 3) {
                vb.emplace_back('Q', false, 1);
            } else {
                vb.emplace_back('K', false, 1);
            }
        }
    }
}

void Board::setPiece(char type, char c, int i, int turn) {
    Piece p = Piece(type, true, turn);
    int j = c - 'a';
    int l = (8 - i) * 8 + j;
    vb[l] = p;
    if (gd) {gd->set(c, i);}
}

void Board::removePiece(char c, int i) {
    Piece p = Piece(' ', false, -1);
    int j = c - 'a';
    int l = (8 - i) * 8 + j;
    vb[l] = p;
    if (gd) {gd->fill(c, i);}
}

bool Board::getEP() {return this->ep;}
void Board::setEP(bool b, char c, int i) {
    this->ep = b;
    this->epchar = c;
    this->epint = i;
} 
char Board::getEPCHAR() {return epchar;}
int Board::getEPINT() {return epint;}

std::ostream &operator<<(std::ostream &out, const Board &b) {
    for (int i = 0; i < 8; ++i) {
        out<<8-i<<" ";
        for (int j = 0; j < 8; ++j) {
            int l = i * 8 + j;
            if (b.vb[l].getType() != ' ') {
                int k = b.vb[l].getOwner();
                char c = b.vb[l].getType();
                if (k == 1) {
                    out<<c;
                } else {
                    char cu = c -'A'+'a';
                    out<<cu;
                }
            } else if ((i + j) % 2 == 0) {
                out<<" ";
            } else {
                out<<"_";
            }
        }
        out<<std::endl;
    }
    out<<std::endl;
    out<<"  abcdefgh";
    return out;
}

void Board::BishopAttack(int x, int y) {
    if (x < y) {
        for (int i = x - 1; i>=0; --i) {
            am[i][y - x + i] = true;
            if (vb[i * 8 + y - x + i].getType() != ' ') {break;}
        }
        for (int j = y + 1; j < 8; ++j) {
            am[x - y + j][j] = true;
            if (vb[(x - y + j) * 8 + j].getType() != ' ') {break;}
        }
    } else {
        for (int i = x + 1; i < 8 ; ++i) {
            am[i][y - x + i] = true;
            if (vb[i * 8 + y - x + i].getType() != ' ') {break;}
        }
        for (int j = y - 1; j>=0; --j) {
            am[x - y + j][j] = true;
            if (vb[(x - y + j) * 8 + j].getType() != ' ') {break;}
        }
    }
    if (x + y < 8) {
        for (int i = x - 1; i>=0; --i) {
            am[i][x + y - i] = true;
            if (vb[i * 8 + x + y - i].getType() != ' ') {break;}
        }
        for (int j = y - 1; j >= 0; --j) {
            am[x + y - j][j] = true;
            if (vb[(x + y - j) * 8 + j].getType() != ' ') {break;}
        }
    } else {
        for (int i = x + 1; i < 8; ++i) {
            am[i][x + y - i] = true;
            if (vb[i * 8 + x + y - i].getType() != ' ') {break;}
        }
        for (int j = y + 1; j < 8; ++j) {
            am[x + y - j][j] = true;
            if (vb[(x + y - j) * 8 + j].getType() != ' ') {break;}
        }
    }
}

void Board::RookAttack(int x, int y) {
    for (int i = x - 1; i >= 0; --i) {
        am[i][y] = true;
        if (vb[i * 8 + y].getType() != ' ') {break;}
    }
    for (int k = x + 1; k < 8; ++k) {
        am[k][y] = true;
        if (vb[k * 8 + y].getType() != ' ') {break;}
    }
    for (int j = y - 1; j >= 0; --j) {
        am[x][j] = true;
        if (vb[x * 8 + j].getType() != ' ') {break;}
    }
    for (int m = y + 1; m < 8; ++m) {
        am[x][m] = true;
        if (vb[x * 8 + m].getType() != ' ') {break;}
    }
}

void Board::PawnAttack(int owner, int x, int y) {
    if (owner == 0) {
        if(y > 0) {am[x + 1][y - 1] = true;}
        if(y < 7) {am[x + 1][y + 1] = true;}
    } else if (owner == 1) {
        if(y > 0) {am[x - 1][y - 1] = true;}
        if(y < 7) {am[x - 1][y + 1] = true;}
    }
}

void Board::KnightAttack(int x, int y) {
    if (x > -3 && x < 6 && y > -2 && y < 7) {am[x+2][y+1] = true;}
    if (x > -3 && x < 6 && y > 0 && y < 9) {am[x+2][y-1] = true;}
    if (x > 1 && x < 10 && y > -2 && y < 7) {am[x-2][y+1] = true;}
    if (x > 1 && x < 10 && y > 0 && y < 9) {am[x-2][y-1] = true;}
    if (x > -2 && x < 7 && y > -3 && y < 6) {am[x+1][y+2] = true;}
    if (x > -2 && x < 7 && y > 1 && y < 10) {am[x+1][y-2] = true;}
    if (x > 0 && x < 9 && y > -3 && y < 6) {am[x-1][y+2] = true;}
    if (x > 0 && x < 9 && y > 1 && y < 10) {am[x-1][y-2] = true;}
}

void Board::KingAttack(int x, int y) {
    if (x > 0 && x < 9 && y > 0 && y < 9) {am[x-1][y-1] = true;}
    if (x > 0 && x < 9 && y > -1 && y < 8) {am[x-1][y] = true;}
    if (x > 0 && x < 9 && y > -2 && y < 7) {am[x-1][y+1] = true;}
    if (x > -1 && x < 8 && y > -1 && y < 8) {am[x][y-1] = true;}
    if (x > -1 && x < 8 && y > -2 && y < 7) {am[x][y+1] = true;}
    if (x > -2 && x < 7 && y > 0 && y < 9) {am[x+1][y-1] = true;}
    if (x > -2 && x < 7 && y > -1 && y < 8) {am[x+1][y] = true;}
    if (x > -2 && x < 7 && y > -2 && y < 7) {am[x+1][y+1] = true;}
}

bool Board::isAttacked(int owner, char c, int i) {
    this->SetFalse();
    for (int j = 0; j < 64; ++j) {
        int x = j / 8;
        int y = j % 8;
        if (x != 8 - i || y != c - 'a') {
            if (vb[j].getOwner() != owner) {
                if (vb[j].getType() == 'B') {this->BishopAttack(x, y);}
                if (vb[j].getType() == 'R') {this->RookAttack(x, y);}
                if (vb[j].getType() == 'Q') {
                    this->BishopAttack(x, y);
                    this->RookAttack(x, y);
                }
                if (vb[j].getType() == 'N') {this->KnightAttack(x, y);}
                if (vb[j].getType() == 'K') {this->KingAttack(x, y);}
                if (vb[j].getType() == 'P') {this->PawnAttack(vb[j].getOwner(), x, y);}
            }
        }
    }
    return am[8 - i][c - 'a'];
}

void Board::SetFalse() {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            am[x][y] = false;
        }
    }
}

void Board::setdisplay(Graphicsdisplay *p) {gd = p;}
