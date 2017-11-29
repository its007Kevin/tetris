#ifndef PIECE_H
#define PIECE_H
#include <cstddef>
#include <vector>
#include <memory>

class Piece {
  // Note the coords represent (row, col) NOT (x,y)
  std::vector<std::vector<int>> coords;
  std::vector<std::vector<int>> potentialCoords;
  int height;
  int width;
  int botLeftx = 0;
  int botLefty = 0;
  char type;
  bool isHeavy = false;
  
 public:
  Piece(char type);
  void rotate(bool isCw);
  void makeIsHeavy();
  void left();
  void right();
  void down();
  void tryPlace();
  void set();
  void revert();
  std::vector<std::vector<int>> getCoords();
  std::vector<std::vector<int>> getPotentialCoords();
  char getType();
};

#endif
