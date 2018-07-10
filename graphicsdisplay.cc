#include <sstream>
#include "graphicsdisplay.h"
#include "board.h" 
#include "piece.h"

Graphicsdisplay::Graphicsdisplay(Board *pb): b{pb} {
    xw.fillRectangle(0, 0, 500, 500, 6);
    for(int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            xw.fillRectangle(20 + y * 60, x * 60 , 60, 60, (x + y) % 2 + 8);
        }
    }
    for (int i = 8; i > 0; --i) {
        std::ostringstream is;
        is<<i;
        char c = 'i' - i;
        std::ostringstream cs;
        cs<<c;
        xw.drawBigString(10, 510 - 60 * i, is.str());
        xw.drawLine(0, 540 - 60 * i, 20, 540 - 60 * i);
        xw.drawBigString(530 - 60 * i, 490, cs.str());
        xw.drawLine(500 - 60 * i, 480, 500 - 60 * i, 500);
    }
    xw.drawLine(0, 0, 20, 0);
    xw.drawLine(500, 480, 500, 500);
}

void Graphicsdisplay::Display() {
    for(int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            int l = x * 8 + y;
            if (b->vb[l].getType() != ' ') {
                int k = b->vb[l].getOwner();
                char c = b->vb[l].getType();
                std::ostringstream cs;
                cs<<c;
                xw.drawBigString(50 + y * 60, 30 + x * 60, cs.str(), 1 - k);
            } else {
                xw.fillRectangle(20 + y * 60, x * 60 , 60, 60, (x + y) % 2 + 8);
            }
        }
    }
}

void Graphicsdisplay::fill(char c, int i) {
    int x = 8 - i;
    int y = c - 'a';
    xw.fillRectangle(20 + y * 60, x * 60 , 60, 60, (x + y) % 2 + 8);
}

void Graphicsdisplay::set(char c, int i) {
    int x = 8 - i;
    int y = c - 'a';
    int l = x * 8 + y;
    xw.fillRectangle(20 + y * 60, x * 60 , 60, 60, (x + y) % 2 + 8);
    int k = b->vb[l].getOwner();
    char co = b->vb[l].getType();
    std::ostringstream cs;
    cs<<co;
    xw.drawBigString(50 + y * 60, 30 + x * 60, cs.str(), 1 - k);
}
