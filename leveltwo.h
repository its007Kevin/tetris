#ifndef LEVELTWO_H
#define LEVELTWO_H
#include "level.h"
#include "piece.h"

class LevelTwo: public Level {
protected:
  bool isHeavy = false;
  char pieces[7] = {'S','Z','I','O','T','L','J'};
public:
  Piece generatePiece() override;
};

#endif
