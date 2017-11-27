#include <iostream>
#include <string>
<<<<<<< HEAD
#include "grid.h"
#include "textdisplay.h"
=======
#include "graphicsdisplay.h"
>>>>>>> cc9e01c533d3f0e1e5fd0b84be918fb56b39a2e2
using namespace std;

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;

  string left = "left";
  string right = "right";
  string down = "down";
  string drop = "drop";
  string cw = "clockwise";
  string ccw = "counterclockwise";
  string lvlup = "levelup";
  string lvldown = "leveldown";
  string norand = "norandom";
  string rand = "random";
  string seq = "sequence";
  string I = "I";
  string J = "J";
  string L = "L";
  string res = "restart";
  string hint = "hint";


  Grid g;

  g.initialize();
  try {
<<<<<<< HEAD
    int r = 18;
    int c = 11;
    TextDisplay *td = new TextDisplay{r, c};
    g.setTextDisplay(td);
    g.init(r, c);
    cout << g;
    while (true) {

=======
  while (cin >> cmd) {
    if (cmd == left) {
      g.moveLeft();
    }
    else if (cmd == right) {
      g.moveRight();
    }
    else if (cmd == down) {
      g.moveDown();
    }
    else if (cmd == drop) {
      g.moveDrop();
    }
    else if (cmd == cw) {
      g.rotateCW();
    }
    else if (cmd == ccw) {
      g.rotateCCW();
    }
    else if (cmd == lvlup) {
      g.levelUp();
    }
    else if (cmd == lvldown) {
      g.levelDown();
>>>>>>> cc9e01c533d3f0e1e5fd0b84be918fb56b39a2e2
    }
    else if (cmd == norand) {
      string file;
      cin >> file;
      g.noRandom(file);
    }
    else if (cmd == rand) {
      g.random();
    }
    else if (cmd == seq) {
      string file;
      cin >> file;
      g.sequence(file);
    }
    else if (cmd == I) {
      g.replaceWithI();
    }
    else if (cmd == J) {
      g.replaceWithJ();
    }
    else if (cmd == L) {
      g.replaceWithL();
    }
    else if (cmd == res) {
      g.restart();
    }
    else if (cmd == hint) {
      g.hint();
    }
    else {
      cout << "Invalid input" << endl;
    }
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
  cout << "Game Over!" << endl;
}
