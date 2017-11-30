#ifndef LEVELTHREE_H
#define LEVELTHREE_H
#include "level.h"
#include "piece.h"

class LevelThree: public Level {
protected:
  bool isHeavy = true;
  int brownBlock = false;
  char pieces[9] = {'S','S','Z','Z','I','O','T','L','J'};
public:
  Piece generatePiece() override;
  Piece generateCenterPiece() override;
};

#endif
