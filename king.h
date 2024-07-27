#ifndef KING_H
#define KING_H

#include <vector>
#include "piece.h"
using namespace std;

class King: public Piece {
    vector<Move> lineOfSight(vector<vector<Piece*>> &, int, int) override;
    vector<Move> possibleMoves(vector<vector<Piece*>> &, int, int) override;

    public:
        King(Colour c, char pieceType);
        virtual ~King();
};

#endif
