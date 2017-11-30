#include "levelthree.h"
#include "piece.h"
#include <cstdlib>
#include <memory>

Piece LevelThree::generatePiece() {
  int randomIndex = rand() % 9;
  return std::make_unique<Piece>(pieces[randomIndex], isHeavy, brownBlock);
}
