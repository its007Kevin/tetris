#include "leveltwo.h"
#include "piece.h"
#include <cstdlib>
#include <memory>

LevelTwo::LevelTwo(int seed) {
	srand(seed);
}

Piece LevelTwo::generatePiece() {
  int randomIndex = rand() % 7;
  Piece generatedPiece{Piece{pieces[randomIndex], 2}};
  return generatedPiece;
}

