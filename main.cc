#include <iostream>
#include <string>
#include <exception>
#include "textdisplay.h"
#include "grid.h"
<<<<<<< HEAD
=======
#include <exception>
#include <fstream>
#include <vector>
>>>>>>> fde9411f92b82155aad2694f93b132f81b7faab6

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
  if (counter == 1) return output;
  else if (counter == 0) throw "Invalid move";
  else throw "Multiple commands contain '" + input + "' as a substring";
}


int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;

  vector<string> commands;

  vector<string> sequence;

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
  commands.emplace_back(res);
  commands.emplace_back(hint);

  Grid g;
  shared_ptr<TextDisplay> td = make_shared<TextDisplay>(18, 11);
  g.setTextDisplay(td);
  g.init(18, 11);
  cout << g;

  try {
  std::ifstream myFileStream{"testsequence.txt"};
  string s;
  while (myFileStream >> s) {
    sequence.emplace_back(s); //add them to the queue
    cout << s << endl;
  }

  for (int i = 0; i < sequence.size(); ++i) {
    if (sequence.at(i) == left) {
      g.left();
    }
    else if (sequence.at(i) == right) {
      g.right();
    }
    else if (sequence.at(i) == down) {
      g.down();
    }
    else if (sequence.at(i) == drop) {
      g.drop();
    }
    else if (sequence.at(i) == cw) {
      g.rotateCW();
    }
    else if (sequence.at(i) == ccw) {
      g.rotateCCW();
    }
    else if (sequence.at(i) == lvlup) {
      try {
        g.levelUp();
        cout << g;
      } catch (char const* err) {
        cout << err << endl;
      }
    }
    else if (sequence.at(i) == lvldown) {
      try {
        g.levelDown();
        cout << g;
      } catch (char const* err) {
        cout << err << endl;
      }
    }
    else if (sequence.at(i) == norand) {
      string file;
      cin >> file;
      g.noRandom(file);
    }
    else if (sequence.at(i) == rand) {
      g.random();
    }
    else if (sequence.at(i) == seq) {
      string file;
      cin >> file;
      g.sequence(file);
    }
    else if (sequence.at(i) == I) {
      g.replacePieceWith('I');
    }
    else if (sequence.at(i) == J) {
      g.replacePieceWith('J');
    }
    else if (sequence.at(i) == L) {
      g.replacePieceWith('L');
    }
    else if (sequence.at(i) == res) {
      g.restart();
    }
    else if (sequence.at(i) == hint) {
      g.hint();
    }
    else {
      cout << "Invalid input" << endl;
      break;
    }
  }
} catch (...) {
  cout << "Missing testsequence.txt" << endl;
}




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
      } catch (char const* err) {
        cout << err << endl;
        continue;
      }
      for (int j = 0; j < repeat; j++) {
        if (cmd == left) {
          g.left();
        }
        else if (cmd == right) {
          g.right();
        }
        else if (cmd == down) {
          g.down();
        }
        else if (cmd == drop) {
          g.drop();
        }
        else if (cmd == cw) {
          g.rotateCW();
        }
        else if (cmd == ccw) {
          g.rotateCCW();
        }
        else if (cmd == lvlup) {
          try {
            g.levelUp();
            cout << g;
          } catch (char const* err) {
            cout << err << endl;
          }
        }
        else if (cmd == lvldown) {
          try {
            g.levelDown();
            cout << g;
          } catch (char const* err) {
            cout << err << endl;
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
          break;
        }
      }
    }
  } catch (ios::failure &) {}
  cout << "Game Over!" << endl;
}
