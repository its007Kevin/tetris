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
  std::shared_ptr<TextDisplay> td; // The text display.
  std::unique_ptr<Piece> currPiece;
 public:
  ~Grid();

  void setTextDisplay(TextDisplay *td);
  bool isGameOver() const;
  void init(int r, int c); // Sets up an a grid with r rows and c columns
  void setPiece(Piece piece, int r, int c);  // Plays piece at row r, col c.

  //added Nov 28
  void unsetPiece(Piece piece);
  void moveLeft();
  void moveRight();
  void moveDown();
  void moveDrop();
  void rotate(bool isCw);
  void levelUp();
  void levelDown();
  void noRandom(std::string file);
  void random();
  void sequence(std::string file);
  void replacePieceWith(char type);
  void restart();
  void hint();

  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
