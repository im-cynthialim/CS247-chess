#include "move.h"

Move::Move(int fromX, int fromY, int toY, int toX) : 
fromX{fromX}, fromY{fromY}, toX{toX}, toY{toY} {}

Move::~Move() {};