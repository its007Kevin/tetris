#include "piece.h"
#include "grid.h"
#include <iostream>
#include <vector>

using namespace std;

Piece::Piece(char type, int level): type{type}, levelGenerated{level} {
  if (type == 'I') {
    coords = {{3, 0}, {3, 1}, {3, 2}, {3, 3}};
  }
  else if (type == 'J') {
    coords = {{3, 0}, {4, 0}, {4, 1}, {4, 2}};
  }
  else if (type == 'L') {
    coords = {{3, 2}, {4, 0}, {4, 1}, {4, 2}};
  }
  else if (type == 'O') {
    coords = {{3, 0}, {3, 1}, {4, 0}, {4, 1}};
  }
  else if (type == 'S') {
    coords = {{4, 0}, {3, 2}, {3, 1}, {4, 1}};
  }
  else if (type == 'Z') {
    coords = {{3, 0}, {3, 1}, {4,1}, {4, 2}};
  }
  else if (type == 'T') {
    coords = {{3, 0}, {3, 1}, {3, 2}, {4, 1}};
  }
  else if (type == '*') {
    coords = {{3, 5}};
  }
  potentialCoords = coords;
}

void Piece::makeHeavy() {
  isHeavy = true;
}

void Piece::removeHeavy() {
  isHeavy = false;
}

bool Piece::checkHeavy() {
  return isHeavy;
}

int Piece::getLevel() {
  return levelGenerated;
}

void Piece::left() {
  for (int i = 0; i < potentialCoords.size(); i++) {
    potentialCoords[i][1]--;
  }
}
void Piece::right() {
  for (int i = 0; i < potentialCoords.size(); i++) {
    potentialCoords[i][1]++;
  }
}

void Piece::down() {
  for (int i = 0; i < potentialCoords.size(); i++) {
    potentialCoords[i][0]++;
  }
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

void Piece::set() {
  coords = potentialCoords;
}

void Piece::revert() {
  potentialCoords = coords;
}

vector<vector<int>> Piece::getCoords() {
  return coords;
}

vector<vector<int>> Piece::getPotentialCoords() {
  return potentialCoords;
}

char Piece::getType() {
  return type;
}

void Piece::incRows(int num) {
  for (int i = 0; i < coords.size(); i++) {
    coords[i][0]++;
  }
}

vector<vector<char>> Piece::render() {
  // Create a grid with 2 rows and 4 columns
  // (This is the max space a piece can take up)
  vector<vector<char>> grid;
  for (int i = 0; i < 2; i++) {
    vector<char> row;
    for (int j = 0; j < 4; j++) {
      row.emplace_back(' ');
    }
    grid.emplace_back(row);
  }
  vector<vector<int>> renderCoords = coords;
  for (int i = 0; i < renderCoords.size(); i++) {
    renderCoords[i][0] -= 3;
  }
  for (int i = 0; i < renderCoords.size(); i++) {
    int row = renderCoords[i][0];
    int col = renderCoords[i][1];
    grid[row][col] = type;
  }
  return grid;
}
