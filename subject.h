#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "observer.h"

class Observer;

class Subject {
protected:
  // std::vector<std::unique_ptr<Observer>> observers;
  std::vector<std::unique_ptr<Observer>> observers;
 public:
  void attach(Observer *o);
  void detach();
  void notifyObservers();
  virtual char getState(int row, int col) const = 0;
  virtual ~Subject() = default;
};

#endif
