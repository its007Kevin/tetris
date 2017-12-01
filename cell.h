#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include "subject.h"
#include "observer.h"
#include "info.h"

class Cell : public Subject {
  int r, c;
  char data;

 public:
  Cell(int r, int c, char data);

  Info getInfo() const override;
  void setData(char d);
  void shiftRows(int n);
};
#endif
