#include "subject.h"
#include "observer.h"
#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
using namespace std;

void Subject::attach(Observer *o) {
  observers.emplace_back(o);
};
void Subject::detach() {
  observers.clear();
}
void Subject::notifyObservers() {
  for (auto &p : observers ) p->notify();
};
