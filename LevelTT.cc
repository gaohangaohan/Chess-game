#include "LevelTT.h"
#include "piece.h"
#include "board.h"

LevelTwo::LevelTwo(Board *pb, int i): Player(pb, i) {}
LevelTwo::~LevelTwo() {}
void LevelTwo::move() {
    for(char c1 = 'a'; c1 <= 'h'; ++c1) {
        for(int n1 = 1; n1 <= 8; ++n1) {
            for(char c2 = 'a'; c2<= 'h'; ++c2) {
                for(int n2 = 1; n2 <= 8; ++n2) {
                    try {
                    if(this->valid(pb, c1, n1, c2, n2)) {
                        bool b1 = false;
                        if(pb->vb[(8 - n2) * 8 + c2 - 'a'].getOwner() == 1 - color) {b1 = true;}
                        int ls = (8 - n1) * 8 + c1 -'a';
                        Board b = *pb;
                        char nck = ck;
                        int nik = ik;
                        b.setdisplay(nullptr);
                        char c = 'P';
                        if (pb->vb[ls].getType() == 'P' && this->pawnValid(pb, c1, n1, c2, n2) &&
                        ((color == 0 && n2 == 1) || (color == 1 && n2 == 8))) {c = 'Q';} 
                        this->validmove(&b, c1, n1, c2, n2, c);
                        bool b2 = false;
                        int lk = this->findcok();
                        if (b.isAttacked(1 - color, lk % 8 + 'a', 8 - lk / 8)) {b2 = true;}
                        if (b.isAttacked(color, ck, ik) || (!b1 && !b2)) {
                            ck = nck;
                            ik = nik;
                            throw Invalid {};
                        } else {
                            this->validmove(pb, c1, n1, c2, n2, c);
                            return;
                        }
                    } else {throw Invalid {};}
                    }
                    catch(Invalid i) {}
                }
            }
        }
    }
    for(char c1 = 'a'; c1 <= 'h'; ++c1) {
        for(int n1 = 1; n1 <= 8; ++n1) {
            for(char c2 = 'a'; c2<= 'h'; ++c2) {
                for(int n2 = 1; n2 <= 8; ++n2) {
                    try {
                    if(this->valid(pb, c1, n1, c2, n2)) {
                        int ls = (8 - n1) * 8 + c1 -'a';
                        Board b = *pb;
                        char nck = ck;
                        int nik = ik;
                        b.setdisplay(nullptr);
                        char c = 'P';
                        if (pb->vb[ls].getType() == 'P' && this->pawnValid(pb, c1, n1, c2, n2) &&
                        ((color == 0 && n2 == 1) || (color == 1 && n2 == 8))) {c = 'Q';}                         
                        this->validmove(&b, c1, n1, c2, n2, c);
                        if (b.isAttacked(color, ck, ik)) {
                            ck = nck;
                            ik = nik;
                            throw Invalid {};
                        } else {
                            this->validmove(pb, c1, n1, c2, n2, c);
                            return;
                        }
                    } else {throw Invalid {};}
                    }
                    catch(Invalid i) {}
                }
            }
        }
    }
}

LevelThree::LevelThree(Board *pb, int i): Player(pb, i) {}
LevelThree::~LevelThree() {}
void LevelThree::move() {
    for(char c1 = 'a'; c1 <= 'h'; ++c1) {
        for(int n1 = 1; n1 <= 8; ++n1) {
            for(char c2 = 'a'; c2<= 'h'; ++c2) {
                for(int n2 = 1; n2 <= 8; ++n2) {
                    try {
                    if(this->valid(pb, c1, n1, c2, n2)) {
                        if(!pb->isAttacked(color, c1, n1)) {throw Invalid{};}
                        int ls = (8 - n1) * 8 + c1 -'a';
                        Board b = *pb;
                        char nck = ck;
                        int nik = ik;
                        b.setdisplay(nullptr);
                        char c = 'P';
                        if (pb->vb[ls].getType() == 'P' && this->pawnValid(pb, c1, n1, c2, n2) &&
                        ((color == 0 && n2 == 1) || (color == 1 && n2 == 8))) {c = 'Q';} 
                        this->validmove(&b, c1, n1, c2, n2, c);
                        if (b.isAttacked(color, ck, ik) || b.isAttacked(color, c2, n2)) {
                            ck = nck;
                            ik = nik;
                            throw Invalid {};
                        } else {
                            this->validmove(pb, c1, n1, c2, n2, c);
                            return;
                        }
                    } else {throw Invalid {};}
                    }
                    catch(Invalid i) {}
                }
            }
        }
    }
    for(char c1 = 'a'; c1 <= 'h'; ++c1) {
        for(int n1 = 1; n1 <= 8; ++n1) {
            for(char c2 = 'a'; c2<= 'h'; ++c2) {
                for(int n2 = 1; n2 <= 8; ++n2) {
                    try {
                    if(this->valid(pb, c1, n1, c2, n2)) {
                        bool b1 = false;
                        if(pb->vb[(8 - n2) * 8 + c2 - 'a'].getOwner() == 1 - color) {b1 = true;}
                        int ls = (8 - n1) * 8 + c1 -'a';
                        Board b = *pb;
                        char nck = ck;
                        int nik = ik;
                        b.setdisplay(nullptr);
                        char c = 'P';
                        if (pb->vb[ls].getType() == 'P' && this->pawnValid(pb, c1, n1, c2, n2) &&
                        ((color == 0 && n2 == 1) || (color == 1 && n2 == 8))) {c = 'Q';} 
                        this->validmove(&b, c1, n1, c2, n2, c);
                        bool b2 = false;
                        int lk = this->findcok();
                        if (b.isAttacked(1 - color, lk % 8 + 'a', 8 - lk / 8)) {b2 = true;}
                        if (b.isAttacked(color, ck, ik) || (!b1 && !b2)) {
                            ck = nck;
                            ik = nik;
                            throw Invalid {};
                        } else {
                            this->validmove(pb, c1, n1, c2, n2, c);
                            return;
                        }
                    } else {throw Invalid {};}
                    }
                    catch(Invalid i) {}
                }
            }
        }
    }
    for(char c1 = 'a'; c1 <= 'h'; ++c1) {
        for(int n1 = 1; n1 <= 8; ++n1) {
            for(char c2 = 'a'; c2<= 'h'; ++c2) {
                for(int n2 = 1; n2 <= 8; ++n2) {
                    try {
                    if(this->valid(pb, c1, n1, c2, n2)) {
                        int ls = (8 - n1) * 8 + c1 -'a';
                        Board b = *pb;
                        char nck = ck;
                        int nik = ik;
                        b.setdisplay(nullptr);
                        char c = 'P';
                        if (pb->vb[ls].getType() == 'P' && this->pawnValid(pb, c1, n1, c2, n2) &&
                        ((color == 0 && n2 == 1) || (color == 1 && n2 == 8))) {c = 'Q';}                         
                        this->validmove(&b, c1, n1, c2, n2, c);
                        if (b.isAttacked(color, ck, ik)) {
                            ck = nck;
                            ik = nik;
                            throw Invalid {};
                        } else {
                            this->validmove(pb, c1, n1, c2, n2, c);
                            return;
                        }
                    } else {throw Invalid {};}
                    }
                    catch(Invalid i) {}
                }
            }
        }
    }
}
