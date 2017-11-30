#ifndef LEVEL_H
#define LEVEL_H
#include "piece.h"

class Level {
public:
  virtual Piece generatePiece() = 0;
};

#endif
