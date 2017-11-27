#include "levelfour.h"
#include "piece.h"
#include <cstdlib>
#include <memory>

Piece LevelFour::generatePiece() {
  int randomIndex = rand() % 9;
  return std::make_unique<Piece>(pieces[randomIndex], isHeavy, brownBlock);
}
