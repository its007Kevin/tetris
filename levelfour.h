#ifndef LEVELFOUR_H
#define LEVELFOUR_H
#include "level.h"
#include "piece.h"

class LevelFour: public Level {
protected:
  bool isHeavy = true;
  int brownBlock = true;
  int pieceCount = 0;
  std::vector<char> seqPieces;
  char pieces[9] = {'S','S','Z','Z','I','O','T','L','J'};
public:
	LevelFour(int seed = 1);
  Piece generatePiece() override;
  Piece generatePiece(std::string file) override;
  Piece generateCenterPiece() override;
};

#endif

