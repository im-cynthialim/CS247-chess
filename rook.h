#ifndef ROOK_H
#define ROOK_H

#include <vector>
#include "piece.h"

using namespace std;

class Rook : public Piece {
    vector<Move> possibleMoves(vector<vector<Piece*>>, int, int) override;
};

#endif