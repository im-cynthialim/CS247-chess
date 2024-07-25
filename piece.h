#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "enums.h"
#include "move.h"

using namespace std;

class Piece {
    Colour colour;
    char pieceType;
    Piece (Colour colour, char pieceType);
    virtual vector<Move> possibleMoves(vector<vector<Piece>>) = 0;
    
    public:
        vector<Move> listMoves (vector<vector<Piece>>);
};

#endif