#ifndef ROOK_H
#define ROOK_H

#include <vector>
#include "piece.h"

using namespace std;

class Rook : public Piece {
    vector<Move> lineOfSight(const vector<vector<Piece*>> &, int, int) override;
    // vector<Move> possibleMoves(const vector<vector<Piece*>> &, int, int) override;
    public: 
        Rook(Colour c, char piecetype);
        virtual ~Rook();
};

#endif