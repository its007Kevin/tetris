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

 public:
  GraphicsDisplay(int gridSize, int winSize);

  void notify(Subject &whoNotified) override;
};
#endif
