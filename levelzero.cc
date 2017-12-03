#include "levelzero.h"
#include "piece.h"
#include <iostream>
#include <fstream>
#include <memory>

LevelZero::LevelZero(std::string filename) {
  //read in pieces from sequence.txt
  std::ifstream myFileStream{filename};
  char c;
  while (myFileStream >> c) {
    pieces.emplace_back(c); //add them to the queue
  }
}

Piece LevelZero::generatePiece() {
  if (pieceCount > pieces.size() - 1) { //reset to the beginning of the queue
    pieceCount = 0;
  }
  Piece generatedPiece{Piece{pieces.at(pieceCount), 0}};
  ++pieceCount; //increment to get next block
  return generatedPiece;
}
