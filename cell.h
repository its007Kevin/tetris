#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include "subject.h"
#include "observer.h"
#include "info.h"

class Cell : public Subject, public Observer {
  int r, c;
  char data;

 public:
  Cell(int r, int c, char data);
  void notify(Subject &whoFrom) override;
  
  Info getInfo() const override;
  void setData(char d);
};
#endif
