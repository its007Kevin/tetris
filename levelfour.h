#ifndef LEVELFOUR_H
#define LEVELFOUR_H
#include "level.h"
#include "piece.h"

class LevelFour: public Level {
protected:
  bool isHeavy = true;
  int brownBlock = true;
  char pieces[9] = {'S','S','Z','Z','I','O','T','L','J'};
public:
  Piece generatePiece() override;
};

#endif
