#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "info.h"
#include "observer.h"

class Subject {
  std::vector<std::shared_ptr<Observer>> observers;
 public:
  void attach(std::shared_ptr<Observer> o);
  void notifyObservers();
  virtual Info getInfo() const = 0;
};

#endif

