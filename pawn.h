#ifndef PAWN_H
#define PAWN_H

#include <vector>
#include "piece.h"

using namespace std;

class Pawn : public Piece {
    vector<Move> lineOfSight(vector<vector<Piece*>> &, int, int) override;
    vector<Move> possibleMoves(vector<vector<Piece*>> &, int, int) override;
    bool getWhiteSpots(int curI, int curJ);
    bool getBlackSpots(int curI, int curJ);
    
    public:
        Pawn(Colour c, char pieceType); 
        virtual ~Pawn();
};

#endif