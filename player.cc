#include <iostream>
#include "player.h"
#include "board.h"
#include "piece.h"

Player::Player(Board *pb, int i): pb{pb}, color{i} {
    for(int l = 0; l < 64; ++l) {
        if(pb->vb[l].getType() == 'K' && pb->vb[l].getOwner() == i) {
            ck = l % 8 + 'a';
            ik = 8 - l / 8;
            break;
        }
    }
}
void Player::move() {}
Player::~Player() {}
bool Player::valid(Board *p, char c1, int n1, char c2, int n2) {
    bool bs = false;
    bool be = true;
    int ls = (8 - n1) * 8 + c1 -'a';
    int le = (8 - n2) * 8 + c2 -'a';
    if (p->vb[ls].getType() != ' ') {
        if (p->vb[ls].getOwner() == color) {
            bs = true;
        }
    }
    if (p->vb[le].getType() != ' ') {
        if (p->vb[le].getOwner() == color) {
            bs = false;
        } else if (p->vb[le].getType() == 'K') {
            bs = false;
        }
    }
    return be && bs;
}

bool Player::rookValid(Board *p, char c1, int n1, char c2, int n2) {
    bool b = false;
    if (c1 == c2) {
        if (n1 < n2) {
            for (int i = 1; i <= n2 - n1; ++i) {
                int l = (8 - n1 - i) *8 + c1 -'a';
                if (p->vb[l].getType() != ' ' && i != n2 - n1) {
                    b = false;
                    break;
                } else {
                    b = true;
                }
            }
        } else if (n1 > n2) {
            for (int i = 1; i <= n1 - n2; ++i) {
                int l = (8 - n2 - i) *8 + c1 -'a';
                if (p->vb[l].getType() != ' ' && i != n1 - n2) {
                    b = false;
                    break;
                } else {
                    b = true;
                }
            }
        }
    } else if (n1 == n2) {
        if (c1 < c2) {
            for (int i = 1; i <= c2 - c1; ++i) {
                int l = (8 - n1) * 8 + c1 + i - 'a';
                if (p->vb[l].getType() != ' ' && i != c2 - c1) {
                    b = false;
                    break;
                } else {
                    b = true;
                }
            }
        } else if (c1 > c2) {
            for (int i = 1; i <= c1 - c2; ++i) {
                int l = (8 - n1) * 8 + c2 + i - 'a';
                if (p->vb[l].getType() != ' ' && i != c1 - c2) {
                    b = false;
                    break;
                } else {
                    b = true;
                }
            }
        }
    }
    return b;
}

bool Player::knightValid(Board *p, char c1, int n1, char c2, int n2) {
    bool b = false;
    int x = n1 - n2;
    int y = c1 - c2;
    if ((x == -2 || x == 2) && (y == -1 || y == 1)) {b = true;}
    if ((y == -2 || y == 2) && (x == -1 || x == 1)) {b = true;}
    return b;
}

bool Player::pawnValid(Board *p, char c1, int n1, char c2, int n2) {
    int ls = (8 - n1) * 8 + c1 -'a';
    int le = (8 - n2) * 8 + c2 -'a';
    if (color == 0) {
        if (c1 == c2 && n2 == n1 - 1 && p->vb[le].getType() == ' ') {
            p->setEP(false, 0, 0);
            return true;
        } else if (n2 == n1 - 1 && (c1 == c2 - 1 || c1 == c2 + 1) && p->vb[le].getType() != ' ') {
            p->setEP(false, 0, 0);
            return true;
        } else if (c1 == c2 && n2 == n1 - 2 && p->vb[le].getType() == ' ' && p->vb[le - 8].getType() == ' '
         && p->vb[ls].nevermove()) {
            p->setEP(true, c2, n2);
            return true;
        }
    } else if (color == 1) {
        if (c1 == c2 && n2 == n1 + 1 && p->vb[le].getType() == ' ') {
            p->setEP(false, 0, 0);
            return true;
        } else if (n2 == n1 + 1 && (c1 == c2 - 1 || c1 == c2 + 1) && p->vb[le].getType() != ' ') {
            p->setEP(false, 0, 0);
            return true;
        } else if (c1 == c2 && n2 == n1 + 2 && p->vb[le].getType() == ' ' && p->vb[le + 8].getType() == ' '
         && p->vb[ls].nevermove()) {
            p->setEP(true, c2, n2);
            return true;
        }        
    }
    return false;
}

int Player::kingValid(Board *p, char c1, int n1, char c2, int n2) {
    int b = 0;
    int x = n1 - n2;
    int y = c1 - c2;
    int l = (8 - n1) * 8 + c1 - 'a';
    if (p->isAttacked(color, c2, n2)) {b = 0;}
    else if (x >= -1 && x <= 1 && y >= -1 && y <= 1) {b = 1;}
    else if (n1 == n2 && c1 == 'e' && c2 == 'g' && n1 % 8 == color && p->vb[l].nevermove()) {
        if (p->vb[l + 1].getType() == ' ' && p->vb[l + 2].getType() == ' ' &&
        p->vb[l + 3].getType() == 'R' && p->vb[l + 3].nevermove() && p->vb[l + 3].getOwner() == color) {
            b = 2;
        }
    }
    else if (n1 == n2 && c1 == 'e' && c2 == 'c' && n1 % 8 == color && p->vb[l].nevermove()) {
        if (p->vb[l - 1].getType() == ' ' && p->vb[l - 2].getType() == ' ' && p->vb[l - 3].getType() == ' '
        && p->vb[l - 4].getType() == 'R' && p->vb[l - 4].nevermove() && p->vb[l - 4].getOwner() == color) {
            b = 3;
        }
    } else {b = 0;}
    return b;
}

bool Player::bishopValid(Board *p, char c1, int n1, char c2, int n2) {
    bool b = false;
    int x1 = c1 - 'a';
    int y1 = 8 - n1;
    int x2 = c2 - 'a';
    if ((c1 - c2 != n1 - n2) && (c1 - c2 != n2 - n1)) {return false;}
    if (c1 > c2 && n1 > n2) {
        for (int i = x1 - 1; i >= x2; --i) {
            if (p->vb[i + 8 * (y1 - i + x1)].getType() != ' ' && i != x2) {
                b = false;
                break;
            } else {
                b = true;
            }
        }
    } else if (c1 > c2 && n1 < n2) {
        for (int i = x1 - 1; i >= x2; --i) {
            if (p->vb[i + 8 * (y1 + i - x1)].getType() != ' ' && i != x2) {
                b = false;
                break;
            } else {
                b = true;
            }
        }
    } else if (c1 < c2 && n1 > n2) {
        for (int i = x1 + 1; i <= x2; ++i) {
            if (p->vb[i + 8 * (y1 + i - x1)].getType() != ' ' && i != x2) {
                b = false;
                break;
            } else {
                b = true;
            }
        }
    } else if (c1 < c2 && n1 < n2) {
        for (int i = x1 + 1; i <= x2; ++i) {
            if (p->vb[i + 8 * (y1 - i + x1)].getType() != ' ' && i != x2) {
                b = false;
                break;
            } else {
                b = true;
            }
        }
    }
    return b;
}

bool Player::isCheck() {return pb->isAttacked(color, ck, ik);}

void Player::validmove(Board *p, char c1, int n1, char c2, int n2, char c) {
    int ls = (8 - n1) * 8 + c1 -'a';
    if (p->vb[ls].getType() == 'R' && this->rookValid(p, c1, n1, c2, n2)) {
        p->setPiece('R', c2, n2, color);
        p->removePiece(c1, n1);
        p->setEP(false, 0, 0);
    } else if (p->vb[ls].getType() == 'B' && this->bishopValid(p, c1, n1, c2, n2)) {
        p->setPiece('B', c2, n2, color);
        p->removePiece(c1, n1);
        p->setEP(false, 0, 0);
    } else if (p->vb[ls].getType() == 'Q' && (this->bishopValid(p, c1, n1, c2, n2) 
    || this->rookValid(p, c1, n1, c2, n2))) {
        p->setPiece('Q', c2, n2, color);
        p->removePiece(c1, n1);
        p->setEP(false, 0, 0);          
    } else if (p->vb[ls].getType() == 'N' && this->knightValid(p, c1, n1, c2, n2)) {
        p->setPiece('N', c2, n2, color);
        p->removePiece(c1, n1); 
        p->setEP(false, 0, 0);   
    } else if (p->vb[ls].getType() == 'K' && this->kingValid(p, c1, n1, c2, n2) != 0) {
        if (this->kingValid(p, c1, n1, c2, n2) == 2) {
            p->setPiece('R', c2 - 1, n2, color);
            p->removePiece('h', n1);
        } else if (this->kingValid(p, c1, n1, c2, n2) == 3) {
            p->setPiece('R', c2 + 1, n2, color);
            p->removePiece('a', n1);
        }
        p->setPiece('K', c2, n2, color);
        p->removePiece(c1, n1);
        p->setEP(false, 0, 0);
        ck = c2;
        ik = n2;    
    } else if (p->vb[ls].getType() == 'P' && this->pawnValid(p, c1, n1, c2, n2)) {
        p->setPiece(c, c2, n2, color);
        p->removePiece(c1, n1);    
    } else if (p->vb[ls].getType() == 'P' && p->getEP() && n1 == p->getEPINT()
                && p->getEPCHAR() == c2) {
        if (n2 == n1 - 1 + 2 * color && (c1 == c2 - 1 || c1 == c2 + 1)) {
            p->removePiece(c2, n1);
            p->setPiece('P', c2, n2, color);
            p->removePiece(c1, n1);
            p->setEP(false, 0, 0);
        } else {throw Invalid{};}
    } else {throw Invalid{};}
}

bool Player::canMove() {
    char nck = ck;
    int nik = ik;
    bool flag = false;
    for(char c1 = 'a'; c1 <= 'h'; ++c1) {
        for (int n1 = 1; n1 <= 8; ++n1) {
            for(char c2 = 'a'; c2 <= 'h'; ++c2) {
                for(int n2 = 1; n2 <= 8; ++n2) {
                    Board b2 = *pb;
                    b2.setdisplay(nullptr);
                    if(this->valid(&b2, c1, n1, c2, n2)) {
                        try{
                            this->validmove(&b2, c1, n1, c2, n2, 'P');
                            flag = true;
                        }
                        catch(Invalid i) {flag = false;}
                    }
                    if(flag) {
                        if (!b2.isAttacked(color, ck, ik)) {
                            ck = nck;
                            ik = nik;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void Player::setK(char c, int i) {
    ck = c;
    ik = i;
}

int Player::findcok() {
    int c = 64;
    for(int i = 0; i < 64; ++i) {
        if(pb->vb[i].getType() == 'K' && pb->vb[i].getOwner() == 1 - color) {
            c = i;
            break;
        } 
    }
    return c;
}
