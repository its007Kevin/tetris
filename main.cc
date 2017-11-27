#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
#include "graphicsdisplay.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;
  // Add code here
  Colour colour = Colour::Black; 

  try {
    while (true) {
      cin >> cmd;
      if (cmd == "new") {
        int n;
        cin >> n;
        // Add code here
        if (n >= 4 && (n%2 == 0)) {
      	  g.setObserver(new GraphicsDisplay{n, 500});
          g.init(n);
        }
      }
      else if (cmd == "play") {
        int r = 0, c = 0;
        cin >> r >> c;
        try {
          g.setPiece(r, c, colour);
          // If valid move, switch colours
          if (colour == Colour::Black) {
            colour = Colour::White;
          } else {
            colour = Colour::Black;
          }
        } catch (InvalidMove e) {} // Otherwise keep the same colour
        // Check if board is full or if there is a winner
        if (g.isFull()) {
          // Output winner to stdout
          if (g.whoWon() == Colour::Black) {
            cout << "Black Wins!" << endl; 
          } else if (g.whoWon() == Colour::White) {
            cout << "White Wins!" << endl;
          } else {
            cout << "Tie!" << endl;
          }
          break; // End input stream
        }
      }
    }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
