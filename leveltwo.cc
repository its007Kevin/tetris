#include "leveltwo.h"
#include "piece.h"
#include <cstdlib>
#include <memory>

Piece LevelTwo::generatePiece() {
  int randomIndex = rand() % 7;
  Piece generatedPiece{Piece{pieces[randomIndex]}};
  return generatedPiece;
}

Piece LevelTwo::generateCenterPiece() {
  Piece centerPiece{Piece{'*'}};
  return centerPiece;
}
