#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "info.h"
class Cell;

class TextDisplay: public Observer {
  std::vector<std::vector<char>> theDisplay;
  int r, c;
 public:
  TextDisplay(int r, int c);

  void notify(Subject &whoNotified) override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
