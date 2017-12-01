#ifndef LEVELONE_H
#define LEVELONE_H
#include "level.h"
#include "piece.h"

class LevelOne: public Level {
protected:
  bool isHeavy = false;
  int brownBlock = false;
  char pieces[12] = {'S','Z','I','I','O','O','T','T','L','L','J','J'};
public:
  Piece generatePiece() override;
  Piece generateCenterPiece() override;
};

#endif
