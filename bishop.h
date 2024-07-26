#ifndef BISHOP_H
#define BISHOP_H

#include <vector>
#include "piece.h"
using namespace std;

class Bishop : public Piece {
    
    vector<Move> possibleMoves(vector<vector<Piece*>>, int, int) override;
    public:
        Bishop(Colour c, char pieceType);
        virtual ~Bishop();
};


#endif