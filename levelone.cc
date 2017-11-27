#include "levelone.h"
#include "piece.h"
#include <cstdlib>
#include <memory>


Piece LevelOne::generatePiece() {
  int randomIndex = rand() % 12;
  return std::make_unique<Piece>(pieces[randomIndex], isHeavy);
  //Piece *newPiece = new Piece{pieces[randomIndex], isHeavy};
  //return newPiece;
}
