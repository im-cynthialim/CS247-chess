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
void Subject::detach(Observer *o) {
    // for (auto it = observers.begin(); it != observers.end(); ++it) {
    //    if (it->get() == o) {
    //         observers.erase(it);
    //         break;
    //     }
    // }
}
void Subject::notifyObservers() {
  for (auto &p : observers ) p->notify();
};
