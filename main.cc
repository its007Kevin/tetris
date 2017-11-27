#include <iostream>
#include <string>
#include "grid.h"
#include "textdisplay.h"
using namespace std;

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  try {
    int r = 18;
    int c = 11;
    TextDisplay *td = new TextDisplay{r, c};
    g.setTextDisplay(td);
    g.init(r, c);
    cout << g;
    while (true) {

    }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
