#include "levelzero.h"
#include "piece.h"
#include <iostream>
#include <fstream>
#include <memory>

LevelZero::LevelZero() {
  //read in pieces from sequence.txt
  std::ifstream myFileStream{"sequence.txt"};
  char c;
  while (myFileStream >> c) {
    pieces.emplace_back(c); //add them to the queue
  }
}

Piece LevelZero::generatePiece() {
  if (pieceCount > pieces.size() - 1) { //reset to the beginning of the queue
    pieceCount = 0;
  }
  Piece generatedPiece{Piece{pieces.at(pieceCount)}};
  ++pieceCount; //increment to get next block
  return generatedPiece;
}

Piece LevelZero::generateCenterPiece() {
  Piece centerPiece{Piece{'*'}};
  return centerPiece;
}
