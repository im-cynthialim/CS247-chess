#ifndef KING_H
#define KING_H

#include <vector>
#include "piece.h"
using namespace std;

class King: public Piece {
    vector<Move> lineOfSight(const vector<vector<Piece*>> &, int, int) override;
    vector<Move> possibleMoves(const vector<vector<Piece*>> &, int, int) override;

    public:
        King(Colour c, char pieceType);
        virtual ~King();
};

#endif
