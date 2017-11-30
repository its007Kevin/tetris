#include "piece.h"
#include "grid.h"
#include <iostream>
#include <vector>

using namespace std;

Piece::Piece(char type): type{type} {
  if (type == 'I') {
    coords = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
  }
  else if (type == 'J') {
    coords = {{2, 0}, {0, 1}, {1, 1}, {2, 1}};
  }
  else if (type == 'L') {
    coords = {{0, 0}, {1, 0}, {2, 0}, {2,1}};
  }
  else if (type == 'O') {
    coords = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
  }
  else if (type == 'S') {
    coords = {{1, 0}, {0, 2}, {0, 1}, {1, 1}};
  }
  else if (type == 'Z') {
    coords = {{0, 0}, {0, 1}, {1,1}, {1, 2}};
  }
  else if (type == 'T') {
    coords = {{0, 0}, {0, 1}, {0, 2}, {1, 1}};
  }
  else if (type == '*') {
    coords = {{0, 0}};
  }
  potentialCoords = coords;
}

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
  int width = xMax - xMin + 1;
  int height = yMax - yMin + 1;
  for (int i = 0; i < potentialCoords.size(); i++) {
    potentialCoords[i][0] = potentialCoords[i][0] - yMax + height - 1;
    potentialCoords[i][1] -= xMin;
    // transpose
    int temp = potentialCoords[i][0];
    potentialCoords[i][0] = potentialCoords[i][1];
    potentialCoords[i][1] = temp;
    potentialCoords[i][1] = height - potentialCoords[i][1] - 1;
    potentialCoords[i][0] = potentialCoords[i][0] + yMax - height + 1 + height - width;
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
  int width = xMax - xMin + 1;
  int height = yMax - yMin + 1;
  for (int i = 0; i < potentialCoords.size(); i++) {
    potentialCoords[i][0] = potentialCoords[i][0] - yMax + height - 1;
    potentialCoords[i][1] -= xMin;
    int temp = potentialCoords[i][0];
    potentialCoords[i][0] = potentialCoords[i][1];
    potentialCoords[i][1] = temp;
    potentialCoords[i][0] = width - potentialCoords[i][0] - 1;
    potentialCoords[i][0] = potentialCoords[i][0] + yMax - height + 1 + height - width;
    potentialCoords[i][1] = potentialCoords[i][1] + xMax - width + 1 - height + width;
  }
}

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
void Piece::left() {
  for (int i = 0; i < potentialCoords.size(); i++) {
    potentialCoords[i][1]++;
  }
}
void Piece::right() {
  for (int i = 0; i < potentialCoords.size(); i++) {
    potentialCoords[i][1]--;
  }
}

char Piece::getType() {
  return type;
}
