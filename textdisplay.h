#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "info.h"
class Cell;

class TextDisplay: public Observer {
  std::vector<std::vector<char>> theDisplay;
  std::vector<std::vector<char>> nextPiece;
  std::vector<std::vector<char>> holdPiece = {std::vector<char>{' '}};
  int score = 0;
  int highScore = 0;
  int r = 0;
  int c = 0;
  int level = 0;
  bool runEnhancement = false;

 public:
  TextDisplay(int r, int c);
  void notify(Subject &whoNotified) override;
  void setLevel(int level);
  void setNextPiece(std::vector<std::vector<char>> nextPiece);
  void setHoldPiece(std::vector<std::vector<char>> holdPiece);
  void setScore(int score);
  void setHighScore(int highScore);
  void enhancementsOn();
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif

