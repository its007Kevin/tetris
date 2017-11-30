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
class Observer;

class Grid {
  int rows;
  int cols;
  std::vector<std::vector<Cell>> theGrid; 
  std::shared_ptr<TextDisplay> td;
  std::shared_ptr<Level> currLevel = std::make_shared<LevelZero>(); 
  Piece currPiece = currLevel->generatePiece();

 public:
  void setTextDisplay(std::shared_ptr<TextDisplay> td);
  bool isGameOver() const;
  void init(int r, int c);

  // Piece Movement specific commands
  void down();
  void left();
  void right();
  void rotateCW();
  void rotateCCW();
  void drop();

  // Piece interactions with board
  void tryPlace();
  void checkPiece(Piece piece);
  void setPiece(Piece piece); 
  void unsetPiece(Piece piece);
  void spawnNextPiece();

  // Not implemented yet
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
