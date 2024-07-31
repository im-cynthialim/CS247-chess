#ifndef PAWN_H
#define PAWN_H

#include <vector>
#include <string>
#include "piece.h"
#include <memory>

using namespace std;

class Pawn : public Piece {
    
    
    bool rightEnPassant = false;
    bool leftEnPassant = false;
    vector<Move> lineOfSight(const  vector<vector<unique_ptr<Piece>>> &, int, int) override;
    bool getWhiteSpots(int curI, int curJ);
    bool getBlackSpots(int curI, int curJ);
    
    public:
        Pawn(Colour c, char pieceType); 
        void setPassant(string dir, bool val);
        unique_ptr<Piece> createNew(Colour colour, char pieceType) override {
        return make_unique<Pawn>(colour, pieceType);
    }
        virtual ~Pawn();
};

#endif
