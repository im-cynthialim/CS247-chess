#include <vector>
#include "enums.h"
#include "piece.h"


// virtual vector<Move> possibleMoves(vector<vector<Piece>>, int, int, int, int) = 0;

// Piece (Colour colour, char pieceType);
// vector<Move> listMoves (vector<vector<Piece>>, int, int, int, int);

Piece::Piece (Colour colour, char pieceType) : colour{colour}, pieceType {pieceType} {}

// getter for piecetype
char Piece::getPieceType() {
    return this->pieceType;
}

// getter for colour
Colour Piece::getColour() {
    return colour;
}

vector<Move> Piece::listMoves (vector<vector<Piece*>> board, int row, int col) {
    return this->possibleMoves(board, row, col);
}

Piece::~Piece() {};