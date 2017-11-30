#include "leveltwo.h"
#include "piece.h"
#include <cstdlib>
#include <memory>

Piece LevelTwo::generatePiece() {
  int randomIndex = rand() % 7;
  return std::make_unique<Piece>(pieces[randomIndex], isHeavy, brownBlock);
}
