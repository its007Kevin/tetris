#include <iostream>
#include "graphicsdisplay.h"
#include "window.h"
#include "info.h"
#include "subject.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int gridSize, int winSize): gridSize{gridSize}, winSize{winSize}, xw{winSize, winSize} {
  xw.fillRectangle(0, 0, winSize, winSize, Xwindow::Blue);
}

void GraphicsDisplay::notify(Subject &whoNotified) {
  // auto info = whoNotified.getInfo();
  // int cellSize = winSize / gridSize;
  // switch(info.colour) {
  //  case Colour::Black:
  //   xw.fillRectangle(info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Black);
  //   break;
  //  case Colour::White:
  //   xw.fillRectangle(info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::White);
  //   break;
  //  default:
  //   xw.fillRectangle(info.col * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Blue);
  // }
}
