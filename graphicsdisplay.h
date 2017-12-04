#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"
#include "info.h"

class Cell;

class GraphicsDisplay: public Observer {
  const int gridSize, winSize;
  Xwindow xw;
  int offset = 20;
  void fillCell(int x, int y, char type);
 public:
  GraphicsDisplay(int gridSize, int winSize);

  void notify(Subject &whoNotified) override;
  void setLevel(int level);
  void setNextPiece(std::vector<std::vector<char>> nextPiece);
  void setHoldPiece(std::vector<std::vector<char>> holdPiece);
  void setScore(int score);
  void setHighScore(int highScore);
  void enableHold();
};
#endif
