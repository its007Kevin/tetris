#ifndef LEVELZERO_H
#define LEVELZERO_H
#include "level.h"
#include "piece.h"
#include <vector>

class LevelZero: public Level {
  int pieceCount = 0; //will reset to the beginning of the textfile
  std::vector<char> pieces;
public:
  LevelZero();
  Piece generatePiece() override;
};

#endif
