#include "levelthree.h"
#include "piece.h"
#include <cstdlib>
#include <memory>
#include <fstream>

LevelThree::LevelThree(int seed) {
  srand(seed);
}

Piece LevelThree::generatePiece() {
  int randomIndex = rand() % 9;
  Piece generatedPiece{Piece{pieces[randomIndex]}};
  generatedPiece.makeHeavy();
  return generatedPiece;
}

Piece LevelThree::generatePiece(std::string file) {
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
