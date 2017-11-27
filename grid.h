#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"
#include "info.h"

class Piece;
class TextDisplay;
class Observer;
class InvalidMove{};

class Grid {
  std::vector<std::vector<Cell>> theGrid;  // The actual grid.
  TextDisplay *td = nullptr; // The text display.

 public:
  ~Grid();

  void setTextDisplay(TextDisplay *td);
  bool isGameOver() const;
  void init(int r, int c); // Sets up an a grid with r rows and c columns
  void setPiece(Piece piece, int r, int c);  // Plays piece at row r, col c.

  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
