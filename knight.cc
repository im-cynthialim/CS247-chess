#include "knight.h"
#include "king.h"
#include "piece.h"
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

Knight::Knight(Colour c, char PieceType): Piece::Piece{c, PieceType} {};

vector<Move> Knight::lineOfSight(const  vector<vector<unique_ptr<Piece>>>& board, int row, int col) {

    vector<Move> validMoves {};
    //counter clockwise motion
    //up 2, 1 right - upper bound not added
    if (row - 2 >= 0 && col + 1 < 8 && (board.at(row-2).at(col+1) == nullptr || board.at(row-2).at(col+1)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
        validMoves.push_back(Move{row, col, row-2, col+1});
    }
    
    //up 1, right 2
    if (row - 1 >= 0 && col + 2 < 8 && (board.at(row-1).at(col+2) == nullptr || board.at(row-1).at(col+2)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
        validMoves.push_back(Move{row, col, row-1, col+2});
    }

    //down 1, right 2
    if (row + 1 < 8 && col + 2 < 8 && (board.at(row+1).at(col+2) == nullptr || board.at(row+1).at(col+2)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
        validMoves.push_back(Move{row, col, row+1, col+2});
    }

    //down 2, right 1
    if (row + 2 < 8 && col + 1 < 8 && (board.at(row+2).at(col+1) == nullptr || board.at(row+2).at(col+1)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
        validMoves.push_back(Move{row, col, row+2, col+1});
    }

    //down 2, left 1
    if (row + 2 < 8 && col - 1 >= 0 && (board.at(row+2).at(col-1) == nullptr || board.at(row+2).at(col-1)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
        validMoves.push_back(Move{row, col, row+2, col-1});
    }

    //down 1, left 2
    if (row + 1 < 8 && col - 2 >= 0 && (board.at(row+1).at(col-2) == nullptr || board.at(row+1).at(col-2)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
        validMoves.push_back(Move{row, col, row+1, col-2});
    }

    //up 1, left 2
    if (row - 1 >=0 && col - 2 >= 0 && (board.at(row-1).at(col-2) == nullptr || board.at(row-1).at(col-2)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
        validMoves.push_back(Move{row, col, row-1, col-2});
    }

    //up 2, left 1
    if (row - 2 >=0 && col - 1 >= 0 && (board.at(row-2).at(col-1) == nullptr || board.at(row-2).at(col-1)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
        validMoves.push_back(Move{row, col, row-2, col-1});
    }

    return validMoves;
}

Knight::~Knight() {}
