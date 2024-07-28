#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>
#include "piece.h"

using namespace std;

class Knight : public Piece {
    vector<Move> lineOfSight(const vector<vector<Piece*>> &, int, int) override;
    vector<Move> possibleMoves(const vector<vector<Piece*>> &, int, int) override;
    public:
        Knight(Colour c, char pieceType); 
        virtual ~Knight();
};

#endif