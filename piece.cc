
#include <vector>
#include "enums.h"
#include "piece.h"


// virtual vector<Move> possibleMoves(vector<vector<Piece>>, int, int, int, int) = 0;

// Piece (Colour colour, char pieceType);
// vector<Move> listMoves (vector<vector<Piece>>, int, int, int, int);

// getter for piecetype
char Piece::getPieceType() {
    return this->pieceType;
}

// getter for colour
Colour Piece::getColour() {
    return colour;
}