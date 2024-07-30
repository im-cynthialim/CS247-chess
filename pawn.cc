#include <vector>
#include <algorithm>
#include "enums.h"
#include "move.h"
#include "king.h"
#include "piece.h"
#include "helperFuncs.h"
#include "pawn.h"
#include <iostream>
#include <string>

using namespace std;

// construct the pawn
Pawn::Pawn(Colour c, char piecetype): Piece::Piece{c, piecetype} {};

void Pawn::setPassant(string dir, bool val) {
    if (dir == "left") {
        leftEnPassant = val;
    }
    else if (dir == "right") {
        rightEnPassant = val;
    }
    return;
}

vector<Move> Pawn::lineOfSight(const vector<vector<Piece*>> &board, int curI, int curJ) {
    // return an array of moves for the pawn
    vector<Move> moves = {};

    // moves for white pawn - moves up board
    if (this->getColour() == WHITE){ 
        // checking to see if pawn does not go out of bounds and if next spot (jump one forward) is empty
        int nextSpot = curI-1;
        if (nextSpot < board.size() && nextSpot >= 0 && board[nextSpot][curJ] == nullptr) {
            moves.push_back(Move{curI, curJ, nextSpot, curJ});
        }

        // checking if the white pawn can attack a piece to the right
        int rightAttackI = curI-1;
        int rightAttackJ = curJ+1;
                
        // board[i+1] because u want to check the size of the next index row, but since its 8x8 probably dont need this,
        // all sizes of each row are the same
        if (rightAttackI >= 0 && rightAttackJ >= 0 && rightAttackI < board.size() && rightAttackJ < board.size() && board[rightAttackI][rightAttackJ] != nullptr
        && board[rightAttackI][rightAttackJ]->getColour() == BLACK) {
            moves.push_back(Move{curI, curJ, rightAttackI, rightAttackJ});
        }

        // checking if the white pawn can attack a piece to the left
        int leftAttackI = curI-1;
        int leftAttackJ = curJ-1;

        if (leftAttackI >= 0 && leftAttackJ >= 0 && leftAttackI < board.size() && leftAttackJ < board.size() && board[leftAttackI][leftAttackJ] != nullptr
        && board[leftAttackI][leftAttackJ]->getColour() == Colour::BLACK) {
            moves.push_back(Move{curI, curJ, leftAttackI, leftAttackJ});
        }

        // check if a pawn can move upwards twice
        // check to see if curI, curJ is a pawn and check to see if its in a specific spot
        // no need to check if out of bounds because the jump two up can never go out of bounds

        if (curI == 6 && board[curI-2][curJ] == nullptr && board[curI-1][curJ] == nullptr) { // see if black pawn can move 2
            moves.push_back(Move{curI, curJ, curI - 2, curJ});
        }
    }


    // black pawn - moves down board
    if (this->getColour() == BLACK){ 
        // this is for checking to see if the piece does not go out of bounds and if next spot (jump one forward) is empty
        int nextSpot = curI+1;
                    
        if (nextSpot < 8 && board[nextSpot][curJ] == nullptr) {
            moves.push_back(Move{curI, curJ, nextSpot, curJ});
        }

        // checking if a black pawn can attack a piece to the right (i.e. down and left)
        int rightAttackI = curI+1;
        int rightAttackJ = curJ-1;

        if (rightAttackI >= 0 && rightAttackJ >= 0 && rightAttackI < 8 && rightAttackJ < 8 && board[rightAttackI][rightAttackJ] != nullptr
        && board[rightAttackI][rightAttackJ]->getColour() == WHITE) {
            moves.push_back(Move{curI, curJ, rightAttackI, rightAttackJ});
        }

        // checking if black pawn can attack a piece to the left
        int leftAttackI = curI+1;
        int leftAttackJ = curJ+1;

        if (leftAttackI >= 0 && leftAttackJ >= 0 && leftAttackI < 8 && leftAttackJ < 8 && board[leftAttackI][leftAttackJ] != nullptr
        && board[leftAttackI][leftAttackJ]->getColour() == Colour::WHITE) {
            moves.push_back(Move{curI, curJ, leftAttackI, leftAttackJ});
        }

        if (curI == 1 && board[curI+2][curJ] == nullptr && board[curI+1][curJ] == nullptr) { // see if black pawn can move 2
            moves.push_back(Move{curI, curJ, curI + 2, curJ});
        }
    }  

    if (this->getColour() == WHITE) {
        if (this->leftEnPassant) {
            moves.push_back(Move{curI, curJ, curI-1, curJ-1});
        }
        if (this->rightEnPassant)
            moves.push_back(Move{curI, curJ, curI-1, curJ+1});

    }
    if (this->getColour() == BLACK) {
        if (leftEnPassant){
            moves.push_back(Move{curI, curJ, curI+1, curJ+1});
        }
        if (rightEnPassant)
        {
            moves.push_back(Move{curI, curJ, curI+1, curJ-1});
        }
  
    }

    return moves;
};

Pawn::~Pawn() {};