#include "move.h"
#include <iostream>

Move::Move(int fromX, int fromY, int toX, int toY) : 
fromX{fromX}, fromY{fromY}, toX{toX}, toY{toY} {}

void Move::getFields() {
    cout <<  "from: " << this->fromX << ", "  << this->fromY << "\n";
    cout <<  "to: " << this->toX << ", "  << this->toY << "\n";
}

bool Move::operator==(const Move &other) const{
    return fromX == other.fromX && fromY == other.fromY && toX == other.toX && toY == other.toY;
}

Move::~Move() {};

