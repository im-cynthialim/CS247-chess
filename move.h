#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include "enums.h"

using namespace std;

class Move {
    int fromX, fromY, toX, toY;
    public: 
        Move(int fromX, int fromY, int toX, int toY);
        void getFields();
        virtual ~Move();

        int getFromX() {
            return fromX;
        }
        int getFromY() {
            return fromY;
        }
        int getToX() {
            return toX;
        }
        int getToY() {
            return toY;
        }
};

#endif