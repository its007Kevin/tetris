#include "levelthree.h"
#include "piece.h"
#include <cstdlib>
#include <memory>

Piece LevelThree::generatePiece() {
  int randomIndex = rand() % 9;
  //Piece *newPiece = new Piece{pieces[randomIndex], isHeavy};
  //return newPiece;

  return std::make_unique<Piece>(pieces[randomIndex], isHeavy);
}
