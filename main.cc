#include <iostream>
#include <string>
#include "textdisplay.h"
#include "grid.h"

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

  // Intialize and print empty board
  Grid g;
  shared_ptr<TextDisplay> td = make_shared<TextDisplay>(15, 11);
  g.setTextDisplay(td);
  g.init(15, 11);
  cout << g;

  try {
    while (cin >> cmd) {
      if (cmd == left) {

      }
      else if (cmd == right) {

      }
      else if (cmd == down) {
        g.pieceCommand(down);
      }
      else if (cmd == drop) {

      }
      else if (cmd == cw) {
        g.pieceCommand(cw);
      }
      else if (cmd == ccw) {
        g.pieceCommand(ccw);
      }
      else if (cmd == lvlup) {
        g.levelUp();
      }
      else if (cmd == lvldown) {
        g.levelDown();
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
        g.replacePieceWith('I');
      }
      else if (cmd == J) {
        g.replacePieceWith('J');
      }
      else if (cmd == L) {
        g.replacePieceWith('L');
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
  catch (ios::failure &) {}
  cout << "Game Over!" << endl;
}
