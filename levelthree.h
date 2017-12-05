#ifndef LEVELTHREE_H
#define LEVELTHREE_H
#include "level.h"
#include "piece.h"

class LevelThree: public Level {
protected:
  int pieceCount = 0; //will reset to the beginning of the textfile
  bool isHeavy = true;
  int brownBlock = false;
  std::vector<char> seqPieces;
  char pieces[9] = {'S','S','Z','Z','I','O','T','L','J'};
public:
	LevelThree(int seed = 1);
  Piece generatePiece() override;
  Piece generatePiece(std::string file) override;
};

#endif

