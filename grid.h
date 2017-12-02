#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <memory>
#include "cell.h"
#include "info.h"
#include "piece.h"
#include "level.h"
#include "levelzero.h"

class TextDisplay;
class GraphicsDisplay;
class Observer;

class Grid {
  int rows;
  int cols;
  std::vector<std::vector<Cell>> theGrid;
  std::shared_ptr<TextDisplay> td;
  std::shared_ptr<GraphicsDisplay> gd;
  int levelCount = 0;
  const int maxLevel = 4;
  const int minLevel = 0;
  int blocksWithoutClear = 0;
  std::shared_ptr<Level> currLevel = std::make_shared<LevelZero>();
  Piece currPiece{'I'};
  Piece nextPiece{'J'};

 public:
  void setTextDisplay(std::shared_ptr<TextDisplay> td);
  void setGraphicsDisplay(std::shared_ptr<GraphicsDisplay> gd);
  bool checkIsGameOver();
  void init(int r, int c);

  // Piece Movement specific commands
  void down();
  void left();
  void right();
  void rotateCW();
  void rotateCCW();
  void drop();
  void dropCenter(Piece&);

  // Piece interactions with board
  void tryPlace();
  void checkPiece(Piece piece);
  void setPiece(Piece piece);
  void unsetPiece(Piece piece);
  void spawnNextPiece();
  void removeFilledRows();
  void restart();

  void levelUp();
  void levelDown();
  void setLevel(int level);
  // Not implemented yet
  void noRandom(std::string file);
  void random();
  void replacePieceWith(char type);
  void hint();

  friend std::ostream &operator<<(std::ostream &out, const Grid &g);

  // Debugging
  void printCellCoords();
};

#endif
