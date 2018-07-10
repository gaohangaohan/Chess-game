#include <iostream>
#include "window.h"

using namespace std;

int main() {
  Xwindow w;

  for (int i = Xwindow::White ; i <= Xwindow::Brown; ++i) {
    w.fillRectangle(50 * i, 200, 50, 250, i);
  }

  w.showAvailableFonts();

  char c;
  cin >> c;

}
