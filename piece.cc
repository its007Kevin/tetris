#include "piece.h"

Piece::Piece(char type, bool isHeavy) {
  this->type = type;
  this->isHeavy = isHeavy;
  //this->g = g;
  if (type == 'I') {
    cells = {{'I', 'I', 'I', 'I'}};
    botLefty = 3;
    botRighty = 3;
  }
  else if (type == 'J') {
    cells = {{'J', ' ', ' '}, {'J', 'J', 'J'}};
    botLefty = 1;
    botRighty = 1;
    botRightx = 2;
  }
  else if (type == 'L') {
    cells = {{' ', ' ', 'L'}, {'L', 'L', 'L'}};
    botLefty = 1;
    botRighty = 1;
    botRightx = 2;
  }
  else if (type == 'O') {
    cells = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    botLefty = 1;
    botRighty = 1;
    botRightx = 1;
  }
  else if (type == 'S') {
    cells = {{' ', 'S', 'S'}, {'S', 'S', ' '}};
    botLefty = 1;
    botRighty = 1;
    botRightx = 2;
  }
  else if (type == 'Z') {
    cells = {{'Z', 'Z', ' '}, {' ', 'Z', 'Z'}};
    botLefty = 1;
    botRighty = 1;
    botRightx = 2;
  }
  else if (type == 'T') {
    cells = {{'T', 'T', 'T'}, {' ', 'T', ' '}};
    botLefty = 1;
    botRighty = 1;
    botRightx = 2;
  }
  else if (type == '*') { 
    cells = {{0, 0}};
  }
}
//rotate: find lowest x, y coord, add 4 to it

void Piece::rotate(bool isCw) {
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
    botRighty = botLefty;
    botRightx = botLeftx + newCells[0].size() - 1;
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
    botLefty = botRighty;
    botLeftx = botRightx - newCells[0].size() + 1;
  }
  cells = newCells;
}

void Piece::moveLeft() {
  botLeftx--;
  botRightx--;
}

void Piece::moveRight() {
  botLeftx++;
  botRightx++;
}
void Piece::moveDown() {
  botLefty--;
  botRighty--;
}
