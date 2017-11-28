#include "piece.h"

Piece::Piece(char type, bool isHeavy) {
  this->type = type;
  this->isHeavy = isHeavy;
  //this->g = g;
  if (type == 'I') {
    cells = {{0,0}, {1,0}, {2,0}, {3,0}};
    botLefty = 3;
    height = 1;
    width = 4;
  }
  else if (type == 'J') {
    cells = {{0,0}, {0, 1}, {1, 1}, {2, 1}};
    botLefty = 1;
    height = 2;
    width = 3;
  }
  else if (type == 'L') {
    cells = {{2, 0}, {0,1}, {1,1}, {2,1}};
    botLefty = 1;
    height = 2;
    width = 3;
  }
  else if (type == 'O') {
    cells = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    botLefty = 1;
    height = 2;
    width = 2;
  }
  else if (type == 'S') {
    cells = {{1, 0}, {2, 0}, {0, 1}, {1, 1}};
    botLefty = 1;
    height = 2;
    width = 3;
  }
  else if (type == 'Z') {
    cells = {{0,0}, {1,0}, {1,1}, {2,1}};
    botLefty = 1;
    height = 2;
    width = 3;
  }
  else if (type == 'T') {
    cells = {{1, 0}, {0, 1}, {1, 1}, {2, 1}};
    botLefty = 1;
    height = 2;
    width = 3;
  }
  else if (type == '*') { 
    cells = {{0, 0}};
    height = 1;
    width = 1;
  }
}
//rotate: find lowest x, y coord, add 4 to it

void Piece::OLDrotate(bool isCw) {
  std::vector<std::vector<int>> newCells;
  if (isCw) {
    int sizeInner = cells[0].size();
    for (int i = 0; i < sizeInner; i++) {
      std::vector<int> newRow;
      int sizeOuter = cells.size();
      for (int j = sizeOuter - 1; j >= 0; j--) {
        newRow.emplace_back(cells[j][i]);
      }
      newCells.emplace_back(newRow);
  
    }
  }
  else {
    int sizeInner = cells[0].size();
    for (int i = sizeInner - 1; i >= 0; i--) {
      std::vector<int> newRow;
      int sizeOuter = cells.size();
      for (int j = 0; j < sizeOuter; j++) {
        newRow.emplace_back(cells[j][i]);
      }
      newCells.emplace_back(newRow);
    }
    botLeftx -= height;
  }
  cells = newCells;
  int temp = height;
  height = width;
  width = temp;
}

void Piece::moveLeft() {
  botLeftx--;
}

void Piece::moveRight() {
  botLeftx++;
}
void Piece::moveDown() {
  botLefty--;
}
