#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <memory>
#include "cell.h"
#include "info.h"
#include "piece.h"

class TextDisplay;
class Observer;

class Grid {
  std::vector<std::vector<Cell>> theGrid; 
  std::shared_ptr<TextDisplay> td;
  Piece currPiece{'J'};
  // std::shared_ptr<Piece> currPiece = std::make_shared<Piece>('J');

 public:

  void setTextDisplay(std::shared_ptr<TextDisplay> td);
  bool isGameOver() const;
  void init(int r, int c);
  void pieceCommand(std::string cmd);
  void setPiece(Piece piece); 
  void unsetPiece(Piece piece);
  void checkPiece(Piece piece);

  // Not implemented yet
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
