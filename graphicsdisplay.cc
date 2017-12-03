#include <iostream>
#include "graphicsdisplay.h"
#include "window.h"
#include "info.h"
#include "subject.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int gridSize, int winSize): gridSize{gridSize}, winSize{winSize}, xw{winSize, winSize} {
  int offset = 25;
  xw.fillRectangle(0, 0, winSize, winSize, Xwindow::White);
  xw.fillRectangle(7 * (winSize/gridSize) - 1, 0, 1, winSize, Xwindow::Black);
  //xw.fillRectangle(0, 0, winSize / gridSize * 7, winSize, Xwindow::Black);
  xw.drawString(20 , 20, "QUADRIS");
  xw.drawString(20 , winSize - 40, "Created by:");
  xw.drawString(20 , winSize - 20, "Eric Wang, Bob Zhang, Kevin Zeng");
  xw.drawString(20, 40, "Next: ");
  xw.drawString(offset, offset + 6 * winSize / gridSize, "Current Score: ");
  xw.drawString(offset, offset + 12 * winSize / gridSize, "Highscore: ");
}

void GraphicsDisplay::notify(Subject &whoNotified) {
  //drawString for score, highscore
  //DrawBigString for Highscore, Score Next Piece, etc. headers
  auto info = whoNotified.getInfo();
  fillCell(info.col + 7, info.row, info.data);
}

void GraphicsDisplay::fillCell(int x, int y, char type) {
  int cellSize = winSize / gridSize;
  switch(type) {
    case 'I':
      xw.fillRectangle(x * cellSize, y * cellSize, cellSize, cellSize, Xwindow::Cyan);
      break;
    case 'J':
      xw.fillRectangle(x * cellSize, y * cellSize, cellSize, cellSize, Xwindow::Orange);
      break;
    case 'L':
      xw.fillRectangle(x * cellSize, y * cellSize, cellSize, cellSize, Xwindow::Blue);
      break;
    case 'O':
      xw.fillRectangle(x * cellSize, y * cellSize, cellSize, cellSize, Xwindow::Yellow);
      break;
    case 'S':
      xw.fillRectangle(x * cellSize, y * cellSize, cellSize, cellSize, Xwindow::Red);
      break;
    case 'Z':
      xw.fillRectangle(x * cellSize, y * cellSize, cellSize, cellSize, Xwindow::Green);
      break;
    case 'T':
      xw.fillRectangle(x * cellSize, y * cellSize, cellSize, cellSize, Xwindow::Magenta);
      break;
    case '*':
      xw.fillRectangle(x * cellSize, y * cellSize, cellSize, cellSize, Xwindow::Brown);
      break;
    default:
      xw.fillRectangle(x * cellSize, y * cellSize, cellSize, cellSize, Xwindow::White);
      break;
  }
  xw.fillRectangle(x * cellSize, y * cellSize, cellSize, 1, Xwindow::White);
  xw.fillRectangle(x * cellSize, y * cellSize, 1, cellSize, Xwindow::White);
  xw.fillRectangle((x + 1) * cellSize, y * cellSize, cellSize, 1, Xwindow::White);
  xw.fillRectangle((x + 1) * cellSize, y * cellSize + cellSize, cellSize, 1, Xwindow::White);
}

void GraphicsDisplay::setLevel(int level) {

}
void GraphicsDisplay::setNextPiece(std::vector<std::vector<char>> nextPiece) {
  for (int i = 0; i < nextPiece.size(); i++) {
    for (int j = 0; j < nextPiece[i].size(); j++) {
      fillCell(i + 1, j + 3, nextPiece[i][j]);
    }
  }
}
void GraphicsDisplay::setScore(int score) {

}
void GraphicsDisplay::setHighScore(int highScore) {

}
