#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>
#include "piece.h"

using namespace std;

class Knight : public Piece {
    vector<Move> lineOfSight(vector<vector<Piece*>> &, int, int) override;
    vector<Move> possibleMoves(vector<vector<Piece*>> &, int, int) override;
    public:
        Knight(Colour c, char pieceType); 
        virtual ~Knight();
};

#endif