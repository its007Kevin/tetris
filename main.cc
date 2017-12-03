#include <iostream>
#include <string>
#include <exception>
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "grid.h"
#include <exception>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include "multiplecommands.h"
#include "invalidmove.h"

using namespace std;

string autoComplete(string input, vector<string> commands) {
  string output = "else";
  int counter = 0;
  for (int i = 0; i < commands.size(); i++) {
    if (commands[i].length() >= input.length() && commands[i].substr(0, input.length()) == input) {
      counter++;
      output = commands[i];
    }
  }
  if (counter == 1) {
    return output;
  } else if (counter == 0) {
    throw InvalidMove();
  } else {
    throw MultipleCommands(input);
  }
}

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  bool createGraphics = true;
  vector<string> commands;

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
  string O = "O";
  string S = "S";
  string Z = "Z";
  string T = "T";
  string res = "restart";
  string hint = "hint";

  commands.emplace_back(left);
  commands.emplace_back(right);
  commands.emplace_back(down);
  commands.emplace_back(drop);
  commands.emplace_back(cw);
  commands.emplace_back(ccw);
  commands.emplace_back(lvlup);
  commands.emplace_back(lvldown);
  commands.emplace_back(norand);
  commands.emplace_back(rand);
  commands.emplace_back(seq);
  commands.emplace_back(I);
  commands.emplace_back(J);
  commands.emplace_back(L);
  commands.emplace_back(O);
  commands.emplace_back(S);
  commands.emplace_back(Z);
  commands.emplace_back(T);
  commands.emplace_back(res);
  commands.emplace_back(hint);

  Grid g;
  // NEED to initialize displays first because setlevel updates textdisplay
  shared_ptr<TextDisplay> td = make_shared<TextDisplay>(18, 11);
  g.setTextDisplay(td);
  if (argc > 1) {
    for(int i = 1; i < argc; i++) {
      if (string(argv[i]) == "-startlevel") {
          istringstream iss{argv[i + 1]};
          int level;
          iss >> level;
          g.setLevel(level);
          i++;
      } else if (string(argv[i]) == "-scriptfile") {
          istringstream iss{argv[i + 1]};
          string file;
          iss >> file;
          // Still need to do
      } else if (string(argv[i]) == "-text") {
          createGraphics = false;
          g.textOnly();
      }
    }
  }
  if (createGraphics) {
    shared_ptr<GraphicsDisplay> gd = make_shared<GraphicsDisplay>(18, 630);
    g.setGraphicsDisplay(gd);
  }
  g.init(18, 11);
  cout << g;

  try {
    while (cin >> cmd) {
      int repeat = 1;
      int i = 0;
      while (i < cmd.length() && isdigit(cmd[i])) {
        i++;
      }
      if (i != 0) repeat = stoi(cmd.substr(0, i));
      cmd = cmd.substr(i, cmd.length());
      if (cmd.length() == 0) {
        cin >> cmd;
      }
      try {
        cmd = autoComplete(cmd, commands);
      } catch (InvalidMove &err) {
        cout << err.what() << endl;
        continue;
      } catch (MultipleCommands &err) {
        cout << err.what() << endl;
        continue;
      }
      if (cmd == left) {
        g.left(repeat);
      }
      else if (cmd == right) {
        g.right(repeat);
      }
      else if (cmd == down) {
        g.down(repeat);
      }
      else if (cmd == drop) {
        g.drop(repeat);
      }
      else if (cmd == cw) {
        g.rotateCW(repeat);
      }
      else if (cmd == ccw) {
        g.rotateCCW(repeat);
      } else {
        for (int j = 0; j < repeat; j++) {
          if (cmd == lvlup) {
            try {
              g.levelUp();
              cout << g;
            } catch (exception& err) {
              cout << err.what() << endl;
              cout << g;
            }
          }
          else if (cmd == lvldown) {
            try {
              g.levelDown();
              cout << g;
            } catch (exception& err) {
              cout << err.what() << endl;
              cout << g;
            }
          }
          else if (cmd == norand) {
            string file;
            cin >> file;
            g.noRandom(file);
          }
          else if (cmd == rand) {
            g.random();
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
          else if (cmd == O) {
            g.replacePieceWith('O');
          }
          else if (cmd == S) {
            g.replacePieceWith('S');
          }
          else if (cmd == Z) {
            g.replacePieceWith('Z');
          }
          else if (cmd == T) {
            g.replacePieceWith('T');
          }
          else if (cmd == res) {
            g.restart();
          }
          else if (cmd == hint) {
            g.hint();
          }
          else if (cmd == seq) {
            string file;
            cin >> file;
            // Try not to nest the entire main function again
          } else {
            cout << "Invalid input" << endl;
            break;
          }
        }
      }
    }
  } catch (...) {
    cout << "Game Over!" << endl;
  }
}
