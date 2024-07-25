#ifndef PAWN_H
#define PAWN_H

#include <vector>
#include "piece.h"

using namespace std;

class Pawn : public Piece {
    vector<Move> possibleMoves(vector<vector<Piece*>>, int, int) override;

    public: 
        Pawn(Colour c, char pieceType);
};

#endif