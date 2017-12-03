#include "levelfour.h"
#include "piece.h"
#include <cstdlib>
#include <memory>
#include <fstream>

LevelFour::LevelFour(int seed) {
  
}

Piece LevelFour::generatePiece() {
  int randomIndex = rand() % 9;
  Piece generatedPiece{Piece{pieces[randomIndex]}};
  generatedPiece.makeHeavy();
  return generatedPiece;
}

Piece LevelFour::generatePiece(std::string file) {
  std::ifstream myFileStream{file};
  char c;
  while (myFileStream >> c) {
    seqPieces.emplace_back(c); //add them to the queue
  }

  if (pieceCount > seqPieces.size() - 1) { //reset to the beginning of the queue
    pieceCount = 0;
  }
  Piece generatedPiece{Piece{seqPieces.at(pieceCount)}};
  ++pieceCount; //increment to get next block
  generatedPiece.makeHeavy();
  return generatedPiece;
}

Piece LevelFour::generateCenterPiece() {
  Piece centerPiece{Piece{'*'}};
  return centerPiece;
}
