#ifndef PAWN_H
#define PAWN_H

#include <vector>
#include <string>
#include "piece.h"

using namespace std;

class Pawn : public Piece {
    bool rightEnPassant = false;
    bool leftEnPassant = false;
    vector<Move> lineOfSight(const vector<vector<Piece*>> &, int, int) override;
    bool getWhiteSpots(int curI, int curJ);
    bool getBlackSpots(int curI, int curJ);
    
    public:
        Pawn(Colour c, char pieceType); 
        void setPassant(string dir, bool val);
        virtual ~Pawn();
};

#endif