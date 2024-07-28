#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "enums.h"
#include "move.h"

using namespace std;

class Piece {
    Colour colour;
    char pieceType;
    
    virtual vector<Move> possibleMoves(const vector<vector<Piece*>> &, int, int) = 0;
    virtual vector<Move> lineOfSight(const vector<vector<Piece*>> &, int, int) = 0;
    
    
    public:
        Piece (Colour colour, char pieceType);
        char getPieceType();
        Colour getColour();
        vector<Move> getPossibleMoves (const vector<vector<Piece*>> &, int, int);
        vector<Move> getLineOfSightMoves(const vector<vector<Piece*>> &, int, int);
        virtual ~Piece();
};

#endif