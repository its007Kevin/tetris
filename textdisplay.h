#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "info.h"
class Cell;

class TextDisplay: public Observer {
  std::vector<std::vector<char>> theDisplay;
  int r, c;
  int level;
  std::vector<std::vector<char>> nextPiece;

 public:
  TextDisplay(int r, int c);
  void notify(Subject &whoNotified) override;
  void setLevel(int level);
  void setNextPiece(std::vector<std::vector<char>> nextPiece);
  std::vector<std::vector<char>> getNextPiece() const;
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
