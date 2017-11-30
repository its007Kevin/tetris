#include "levelfour.h"
#include "piece.h"
#include <cstdlib>
#include <memory>

Piece LevelFour::generatePiece() {
  int randomIndex = rand() % 9;
  Piece generatedPiece{Piece{pieces[randomIndex]}};
  return generatedPiece;
}
