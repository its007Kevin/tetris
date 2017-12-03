#include "levelone.h"
#include "piece.h"
#include <cstdlib>
#include <memory>

LevelOne::LevelOne(int seed) {
	srand(seed);
}

Piece LevelOne::generatePiece() {
  int randomIndex = rand() % 12;
  Piece generatedPiece{Piece{pieces[randomIndex], 1}};
  return generatedPiece;
}
