#include <iostream>
#include "graphicsdisplay.h"
#include "window.h"
#include "info.h"
#include "subject.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int gridSize, int winSize): gridSize{gridSize}, winSize{winSize}, xw{winSize, winSize} {
  xw.fillRectangle(0, 0, winSize, winSize, Xwindow::White);
  //border
  //left
  xw.fillRectangle(7 * (winSize/gridSize) - 4 - offset, offset - 4,
                    4, winSize - 3 * winSize / gridSize + 9,
                    Xwindow::Black);
  //right
  xw.fillRectangle(winSize - offset + 1, offset - 4,
                    4, winSize - 3 * winSize / gridSize + 9,
                    Xwindow::Black);
  //top
  xw.fillRectangle(7 * (winSize/gridSize) - 4 - offset, offset - 4,
                    winSize - 7 * (winSize / gridSize) + 5, 4,
                    Xwindow::Black);
  //bottom
  xw.fillRectangle(7 * (winSize/gridSize) - 4 - offset, winSize - 3 * winSize / gridSize + offset + 1,
                    winSize - 7 * (winSize / gridSize) + 5, 4,
                    Xwindow::Black);
  //xw.fillRectangle(0, 0, winSize / gridSize * 7, winSize, Xwindow::Black);
  xw.drawString(offset , offset, "QUADRIS");
  xw.drawString(offset , winSize - 40, "Created by:");
  xw.drawString(offset , winSize - 20, "Eric Wang, Bob Zhang, Kevin Zeng");
  xw.drawString(offset, 40, "Next: ");
  xw.drawString(offset, offset + 5 * winSize / gridSize, "Current Score: ");
  xw.drawString(offset, offset + 10 * winSize / gridSize, "Highscore: ");
  // for (int i = 0; i < 500; i += 25) {
  //   for (int j = 0; j < 500; j+= 25) {
  //   xw.fillRectangle(i, j, 25, 25, Xwindow::Cyan);
  //   }
  // }
}

void GraphicsDisplay::notify(Subject &whoNotified) {
  //drawString for score, highscore
  //DrawBigString for Highscore, Score Next Piece, etc. headers
  auto info = whoNotified.getInfo();
  if (info.row <= 2) return;
  fillCell(info.col + 7, info.row - 3, info.data);
}

void GraphicsDisplay::fillCell(int x, int y, char type) {
  int cellSize = winSize / gridSize;
  x = x * cellSize - offset;
  y = y * cellSize + offset;
  int colour = Xwindow::White;
  switch(type) {
    case 'I':
      colour = Xwindow::Cyan;
      break;
    case 'J':
      colour = Xwindow::Orange;
      break;
    case 'L':
      colour = Xwindow::Blue;
      break;
    case 'O':
      colour = Xwindow::Yellow;
      break;
    case 'S':
      colour = Xwindow::Red;
      break;
    case 'Z':
      colour = Xwindow::Green;
      break;
    case 'T':
      colour = Xwindow::Magenta;
      break;
    case '*':
      colour = Xwindow::Brown;
      break;
    default:
      colour = Xwindow::White;
      break;
  }
  xw.fillRectangle(x, y, cellSize, cellSize, colour);
  if (type == ' ') return;
  xw.fillRectangle(x, y, cellSize, 1, Xwindow::White);
  xw.fillRectangle(x, y, 1, cellSize, Xwindow::White);
  xw.fillRectangle(x + cellSize, y, 1, cellSize, Xwindow::White);
  xw.fillRectangle(x, y + cellSize, cellSize, 1, Xwindow::White);
}

void GraphicsDisplay::setLevel(int level) {

}
void GraphicsDisplay::setNextPiece(std::vector<std::vector<char>> nextPiece) {
  for (int i = 0; i < nextPiece.size(); i++) {
    for (int j = 0; j < nextPiece[i].size(); j++) {
      fillCell(j + 1, i + 1, nextPiece[i][j]);
    }
  }
}
void GraphicsDisplay::setScore(int score) {
  xw.drawString(offset, offset + 20 + 4 * winSize / gridSize, "Current Score: ");
}
void GraphicsDisplay::setHighScore(int highScore) {
  xw.drawString(offset, offset + 20 + 8 * winSize / gridSize, "Highscore: ");
}
