#include <vector>
#include "enums.h"
#include "piece.h"
#include <iostream>
#include <memory>

Piece::Piece (Colour colour, char pieceType) : colour{colour}, pieceType {pieceType} {}

// getter for piecetype
char Piece::getPieceType() {
    return this->pieceType;
}

// getter for colour
Colour Piece::getColour() {
    return colour;
}

vector<Move> Piece::getPossibleMoves (const  vector<vector<unique_ptr<Piece>>> &board, int row, int col)  {
    return this->possibleMoves(board, row, col);
}

vector<Move> Piece::getLineOfSightMoves (const  vector<vector<unique_ptr<Piece>>> &board, int row, int col)  {
    return this->lineOfSight(board, row, col);
}

unique_ptr<Piece> Piece::getCreateNew(Colour colour, char pieceType) {
    return this->createNew(colour, pieceType);
}


Piece::~Piece() {};
