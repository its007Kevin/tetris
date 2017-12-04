#include <iostream>
#include "graphicsdisplay.h"
#include "window.h"
#include "info.h"
#include "subject.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int gridSize, int winSize): gridSize{gridSize}, winSize{winSize}, xw{winSize, winSize} {
  //xw.fillRectangleRGB(0, 0, winSize, winSize, 250000, 250000, 250000);
  //xw.fillRectangle(0, 0, winSize, winSize, Xwindow::White);
  //grid lines
  int x = 8 * (winSize / gridSize) - offset;
  while (x < winSize - offset) {
    xw.fillRectangleRGB(x, offset - 4, 1, winSize - 3 * winSize / gridSize + 9, 250000, 250000, 250000);
    x += winSize / gridSize;
  }
  int y = offset + winSize / gridSize;
  while (y < winSize - 3 * winSize / gridSize + offset + 1) {
    xw.fillRectangleRGB(7 * (winSize/gridSize) - 4 - offset, y, winSize - 7 * (winSize / gridSize) + 5, 1, 250000, 250000, 250000);
    y += winSize / gridSize;
  }

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

   /*int i = 14;
   for (int i = 0; i < 500; i += 25) {
     for (int j = 0; j < 500; j+= 25) {
     xw.fillRectangle(i, j, 25, 25, i);
     cout << i << endl;
     i++;
     }
   }*/
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
  xw.fillRectangleRGB(x, y, cellSize, 1, 250000, 250000, 250000);
  xw.fillRectangleRGB(x, y, 1, cellSize, 250000, 250000, 250000);
  xw.fillRectangleRGB(x + cellSize, y, 1, cellSize, 250000, 250000, 250000);
  xw.fillRectangleRGB(x, y + cellSize, cellSize, 1, 250000, 250000, 250000);
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
  xw.fillRectangle(offset, offset + 4 + 5 * winSize / gridSize, 100, 16, Xwindow::White);
  xw.drawString(offset, offset + 20 + 5 * winSize / gridSize, to_string(score));
}
void GraphicsDisplay::setHighScore(int highScore) {
  xw.fillRectangle(offset, offset + 4 + 10 * winSize / gridSize, 100, 16, Xwindow::White);
  xw.drawString(offset, offset + 20 + 10 * winSize / gridSize, to_string(highScore));
}
