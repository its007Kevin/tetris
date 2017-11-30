#include "levelone.h"
#include "piece.h"
#include <cstdlib>
#include <memory>

Piece LevelOne::generatePiece() {
  int randomIndex = rand() % 12;
  Piece generatedPiece{Piece{pieces[randomIndex]}};
  return generatedPiece;
}

Piece LevelOne::generateCenterPiece() {
  Piece centerPiece{Piece{'*'}};
  return centerPiece;
}
