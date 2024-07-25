#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include "enums.h"

using namespace std;

class Move {
    int fromX, fromY, toY, toX;
    public: 
        Move(int fromX, int fromY, int toY, int toX);
        virtual ~Move();
};

#endif