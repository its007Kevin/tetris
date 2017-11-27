#ifndef LEVELZERO_H
#define LEVELZERO_H
#include "level.h"
#include "piece.h"
#include <vector>

class LevelZero: public Level {
  bool isHeavy = false;
  int blockCount = 0; //will reset to the beginning of the textfile
  std::vector<char> blocks;
public:
  Piece generatePiece() override;
};

#endif
