#ifndef _GRAPHICSDISPLAY_H_
#define _GRAPHICSDISPLAY_H_
#include "window.h"

class Board;
class Graphicsdisplay {
    Xwindow xw;
    Board *b;
public:
    Graphicsdisplay(Board *pb);
    void Display();
    void fill(char c, int i);
    void set(char c, int i);
};
#endif
