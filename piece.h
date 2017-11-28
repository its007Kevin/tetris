#ifndef QUADRIS_PIECE_H
#define QUADRIS_PIECE_H
#include <cstddef>
#include <vector>

struct Piece {
  std::vector<std::vector<int>> cells;
  int botLeftx = 0;
  int botLefty = 0;
  int botRightx = 0;
  int botRighty = 0;
  char type;
  bool isHeavy;
  
 public:
  Piece(char type, bool isHeavy);
  void rotate(bool isCw);
  void moveLeft();
  void moveRight();
  void moveDown();
};
#endif
