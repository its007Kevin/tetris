#include "levelthree.h"
#include "piece.h"
#include <cstdlib>
#include <memory>

Piece LevelThree::generatePiece() {
  int randomIndex = rand() % 9;
  Piece generatedPiece{Piece{pieces[randomIndex]}};
  return generatedPiece;
}

Piece LevelThree::generateCenterPiece() {
  Piece centerPiece{Piece{'*'}};
  return centerPiece;
}
