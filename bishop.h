#ifndef BISHOP_H
#define BISHOP_H

#include <vector>
#include "piece.h"
using namespace std;

class Bishop : public Piece {
    vector<Move> lineOfSight(const vector<vector<Piece*>> &, int, int) override;
    vector<Move> possibleMoves(const vector<vector<Piece*>> &, int, int) override;
    public:
        Bishop(Colour c, char pieceType);
        virtual ~Bishop();
};


#endif