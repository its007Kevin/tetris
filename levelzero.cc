#include "levelzero.h"
#include "piece.h"
#include <iostream>
#include <fstream>
#include <memory>

Piece LevelZero::generatePiece() {
  //read in sequence.txt
  std::ifstream myFileStream{"sequence.txt"};
  char c;
  while (myFileStream >> c) {
    blocks.emplace_back(c); //add them to the queue
  }

  if (blockCount > blocks.size() - 1) { //reset to the beginning of the queue
    blockCount = 0;
  }

  //auto newPiece = std::make_unique<Piece>(pieces[blockCount], isHeavy);
  //Piece *newPiece = new Piece{blocks[blockCount], isHeavy};

  ++blockCount; //increment to get next block
  return std::make_unique<Piece>(blocks.at(blockCount), isHeavy);
}
