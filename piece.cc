#include "piece.h"
#include "grid.h"
#include <iostream>
#include <vector>

using namespace std;

Piece::Piece(char type): type{type} {
  if (type == 'I') {
    coords = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
    //botLefty = 3;
    //height = 4;
    //width = 1;
  }
  else if (type == 'J') {
//    coords = {{2, 3}, {0, 4}, {1, 4}, {2, 4}};
coords = {{2, 0}, {0, 1}, {1, 1}, {2, 1}};
    //botLefty = 1;
    //height = 3;
    //width = 2;
  }
  else if (type == 'L') {
    coords = {{0, 0}, {1, 0}, {2, 0}, {2,1}};
    //botLefty = 1;
    //height = 3;
    //width = 2;
  }
  else if (type == 'O') {
    coords = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    //botLefty = 1;
    //height = 2;
    //width = 2;
  }
  else if (type == 'S') {
    coords = {{1, 0}, {0, 2}, {0, 1}, {1, 1}};
    //botLefty = 1;
    //height = 2;
    //width = 3;
  }
  else if (type == 'Z') {
    coords = {{0, 0}, {0, 1}, {1,1}, {1, 2}};
    //botLefty = 1;
    //height = 2;
    //width = 3;
  }
  else if (type == 'T') {
    coords = {{0, 0}, {0, 1}, {0, 2}, {1, 1}};
    //botLefty = 1;
    //height = 2;
    //width = 3;
  }
  else if (type == '*') {
    coords = {{0, 0}};
    //height = 1;
    //width = 1;
  }
  potentialCoords = coords;
}
//rotate: find lowest x, y coord, add 4 to it

void Piece::makeIsHeavy() {
  isHeavy = true;
}

void Piece::rotateCW() {
  int xMax = potentialCoords[0][1];
  int yMax = potentialCoords[0][0];
  int xMin = potentialCoords[0][1];
  int yMin = potentialCoords[0][0];
  for (int i = 0; i < potentialCoords.size(); i++) {
    if (potentialCoords[i][0] > yMax) yMax = potentialCoords[i][0];
    if (potentialCoords[i][0] < yMin) yMin = potentialCoords[i][0];
    if (potentialCoords[i][1] > xMax) xMax = potentialCoords[i][1];
    if (potentialCoords[i][1] < xMin) xMin = potentialCoords[i][1];
  }
  //int botLeftx;
  //int botLefty;
  int width = xMax - xMin;
  int height = yMax - yMin;
  for (int i = 0; i < potentialCoords.size(); i++) {
    potentialCoords[i][0] = potentialCoords[i][0] - yMax + height - 1;
    potentialCoords[i][1] -= xMin;
    // transpose
    //coords[i].reverse(0, coords[i].size());
    int temp = potentialCoords[i][0];
    potentialCoords[i][0] = potentialCoords[i][1];
    potentialCoords[i][1] = temp;
    //
    potentialCoords[i][1] = height - potentialCoords[i][1] - 1;

    potentialCoords[i][0] = potentialCoords[i][0] + xMax - width + 1;
    if (width > height) potentialCoords[i][0] -= width - height;
    potentialCoords[i][1] += xMin;
  }
}

void Piece::rotateCCW() {
  int xMax = potentialCoords[0][1];
  int yMax = potentialCoords[0][0];
  int xMin = potentialCoords[0][1];
  int yMin = potentialCoords[0][0];
  for (int i = 0; i < potentialCoords.size(); i++) {
    if (potentialCoords[i][0] > yMax) yMax = potentialCoords[i][0];
    if (potentialCoords[i][0] < yMin) yMin = potentialCoords[i][0];
    if (potentialCoords[i][1] > xMax) xMax = potentialCoords[i][1];
    if (potentialCoords[i][1] < xMin) xMin = potentialCoords[i][1];
  }
  //int botLeftx;
  //int botLefty;
  int width = xMax - xMin;
  int height = yMax - yMin;
  for (int i = 0; i < potentialCoords.size(); i++) {
    potentialCoords[i][0] = potentialCoords[i][0] - yMax + height - 1;
    potentialCoords[i][1] -= xMin;
    // transpose
    //coords[i].reverse(0, coords[i].size());
    int temp = potentialCoords[i][0];
    potentialCoords[i][0] = potentialCoords[i][1];
    potentialCoords[i][1] = temp;
    //
    potentialCoords[i][0] = width - potentialCoords[i][0] - 1;

    potentialCoords[i][0] = potentialCoords[i][0] + xMax - width + 1;
    if (width > height) potentialCoords[i][0] -= width - height;
    potentialCoords[i][1] += xMin;
  }
}

// void Piece::OLDrotate(bool isCw) {
//   std::vector<std::vector<int>> newcoords;
//   if (isCw) {
//     int sizeInner = coords[0].size();
//     for (int i = 0; i < sizeInner; i++) {
//       std::vector<int> newRow;
//       int sizeOuter = coords.size();
//       for (int j = sizeOuter - 1; j >= 0; j--) {
//         newRow.emplace_back(coords[j][i]);
//       }
//       newcoords.emplace_back(newRow);

//     }
//   }
//   else {
//     int sizeInner = coords[0].size();
//     for (int i = sizeInner - 1; i >= 0; i--) {
//       std::vector<int> newRow;
//       int sizeOuter = coords.size();
//       for (int j = 0; j < sizeOuter; j++) {
//         newRow.emplace_back(coords[j][i]);
//       }
//       newcoords.emplace_back(newRow);
//     }
//     botLeftx -= height;
//   }
//   coords = newcoords;
//   int temp = height;
//   height = width;
//   width = temp;
// }

vector<vector<int>> Piece::getCoords() {
  return coords;
}

vector<vector<int>> Piece::getPotentialCoords() {
  return potentialCoords;
}

void Piece::set() {
  coords = potentialCoords;
}

void Piece::revert() {
  potentialCoords = coords;
}

void Piece::down() {
  for (int i = 0; i < potentialCoords.size(); i++) {
    potentialCoords[i][0]++;
  }
}

char Piece::getType() {
  return type;
}
