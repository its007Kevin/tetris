#ifndef PIECE_H
#define PIECE_H
#include <cstddef>
#include <vector>
#include <memory>

class Piece {
  // coords represent (row, col) NOT (x,y)
  std::vector<std::vector<int>> initialCoords;
  std::vector<std::vector<int>> coords;
  std::vector<std::vector<int>> potentialCoords;
  char type;
  bool isHeavy = false;
  int levelGenerated = 0;

 public:
  Piece(char type, int level);
  void makeHeavy();
  void removeHeavy();
  bool checkHeavy();
  int getLevel();
  void incRows(int num);

  // Piece movement
  void left();
  void right();
  void down();
  void rotateCW();
  void rotateCCW();

  // Manipulate Piece
  void set();
  void revert();
  void reset();
  std::vector<std::vector<int>> getCoords();
  std::vector<std::vector<int>> getPotentialCoords();
  char getType();

  // View
  std::vector<std::vector<char>> render();
};

#endif
