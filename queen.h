#ifndef QUEEN_H
#define QUEEN_H

#include <vector>
#include "piece.h"
using namespace std;

class Queen : public Piece {
    vector<Move> lineOfSight(const vector<vector<Piece*>> &, int, int) override;
    public:
        Queen(Colour c, char pieceType);
        virtual ~Queen();
};


#endif
