#include "rook.h"
#include "king.h"
#include "piece.h"
#include <iostream>
#include <memory>
#include <algorithm>

Rook::Rook(Colour c, char PieceType): Piece::Piece{c, PieceType} {};

vector<Move> Rook::lineOfSight(const vector<vector<Piece*>> &board, int row, int col) { // return all general valid moves (empty squares or captures)
    vector<Move> validMoves {};
    int i = row + 1;

    //vertical moves
     while (i < 8) { // downward moves
        if(board.at(i).at(col) == nullptr) { // empty square
            validMoves.push_back(Move{row, col, i, col});
        }
        else if (board.at(i).at(col)->getColour() != this->getColour()) { // different colour means capture, can't move beyond
            validMoves.push_back(Move{row, col, i, col});
            break;
        }
        else { // same colour at square
            break;
        }
        ++i;
    }

    //check left side <--- 
    i = row - 1;

    while (i >= 0) { 
         if(board.at(i).at(col) == nullptr) { // empty square
            validMoves.push_back(Move{row, col, i, col});
        }
        else if (board.at(i).at(col)->getColour() != this->getColour()) { // different colour means capture, can't move beyond
            validMoves.push_back(Move{row, col, i, col});
            break;
        }
        else { // same colour at square
            break;
        }
        --i;
    }

    //check vertical moves
    int j = col + 1;

    while (j < 8) { //check top/bottom moves (depends on colour)
        if(board.at(row).at(j) == nullptr) { // empty square
        validMoves.push_back(Move{row, col, row, j});
    }
    else if (board.at(row).at(j)->getColour() != this->getColour()) { // different colour means capture, can't move beyond
        validMoves.push_back(Move{row, col, row, j});
        break;
    }
    else { // same colour at square
        break;
    }
    ++j;
    }

    //check top/bottom moves (depends on colour)   
    j = col - 1;

    while (j >= 0) { 
        if(board.at(row).at(j) == nullptr) { // empty square
        validMoves.push_back(Move{row, col, row, j});
    }
    else if (board.at(row).at(j)->getColour() != this->getColour()) { // different colour means capture, can't move beyond
        validMoves.push_back(Move{row, col, row, j});
        break;
    }
    else { // same colour at square
        break;
    }
    --j;
    }

    return validMoves;
}

Rook::~Rook() {};
