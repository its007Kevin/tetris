#include <iostream>
#include "graphicsdisplay.h"
#include "window.h"
#include "info.h"
#include "subject.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int gridSize, int winSize): gridSize{gridSize}, winSize{winSize}, xw{winSize, winSize} {
  int offset = 25;
  xw.fillRectangle(0, 0, winSize, winSize, Xwindow::White);
  //xw.fillRectangle(0, 0, winSize / gridSize * 7, winSize, Xwindow::Black);
  //xw.drawBigString(offset, offset, "NEXT PIECE");
  //xw.drawBigString(offset, offset + 6 * winSize / gridSize, "CURRENT SCORE");
  //xw.drawBigString(offset, offset + 12 * winSize / gridSize, "HIGHSCORE");
}

void GraphicsDisplay::notify(Subject &whoNotified) {
  //drawString for score, highscore
  //DrawBigString for Highscore, Score Next Piece, etc. headers
  auto info = whoNotified.getInfo();
  int cellSize = winSize / gridSize;
  switch(info.data) {
    case 'I':
      xw.fillRectangle((info.col + 7) * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Cyan);
      break;
    case 'J':
      xw.fillRectangle((info.col + 7) * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Orange);
      break;
    case 'L':
      xw.fillRectangle((info.col + 7) * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Blue);
      break;
    case 'O':
      xw.fillRectangle((info.col + 7) * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Yellow);
      break;
    case 'S':
      xw.fillRectangle((info.col + 7) * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Red);
      break;
    case 'Z':
      xw.fillRectangle((info.col + 7) * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Green);
      break;
    case 'T':
      xw.fillRectangle((info.col + 7) * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Magenta);
      break;
    case '*':
      xw.fillRectangle((info.col + 7) * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::Brown);
      break;
    default:
      xw.fillRectangle((info.col + 7) * cellSize, info.row * cellSize, cellSize, cellSize, Xwindow::White);
      break;
  }

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
