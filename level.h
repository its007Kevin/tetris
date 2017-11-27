#ifndef LEVEL_H
#define LEVEL_H
#include "piece.h"

class Level {
protected:
  //bool isHeavy;
public:
  virtual Piece generatePiece() = 0;
};

#endif
