#include <iostream>
#include "human.h"
#include "piece.h"
#include "board.h"

Human::Human(Board *pb, int i): Player(pb, i) {}
void Human::move() {
    char c1;
    int n1;
    char c2;
    int n2;
    std::cin>>c1>>n1>>c2>>n2;
    if(c1 >= 'a' && c1 <='h' && c2 >= 'a' && c2 <= 'h'
    && n1 >= 1 && n1 <= 8 && n2 >= 1 && n2 <= 8 && this->valid(pb, c1, n1, c2, n2)) {
        int ls = (8 - n1) * 8 + c1 -'a';
        Board b = *pb;
        char nck = ck;
        int nik = ik;
        b.setdisplay(nullptr);
        char c = 'P';
        if (pb->vb[ls].getType() == 'P' && this->pawnValid(pb, c1, n1, c2, n2) &&
        ((color == 0 && n2 == 1) || (color == 1 && n2 == 8))) {std::cin>>c;} 
        this->validmove(&b, c1, n1, c2, n2, c);
        if (b.isAttacked(color, ck, ik)) {
            ck = nck;
            ik = nik;
            throw Invalid {};
        } else {
            this->validmove(pb, c1, n1, c2, n2, c);
        }
    } else {throw Invalid {};}
}
Human::~Human() {}

LevelOne::LevelOne(Board *pb, int i): Player(pb, i) {}
LevelOne::~LevelOne() {}
void LevelOne::move() {
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
