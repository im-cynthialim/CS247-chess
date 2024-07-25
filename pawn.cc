#include <vector>
#include "enums.h"
#include "game.h"
#include "move.h"
#include "piece.h"
#include "pawn.h"
using namespace std;

// construct the pawn
Pawn::Pawn(Colour c, char piecetype): Piece::Piece{c, piecetype} {};

vector<Move> Pawn::possibleMoves(vector<vector<Piece*>> board, int curI, int curJ) {
    // return an array of moves for the pawn
    vector<Move> moves;

    //moves for white pawn - moves up board
    if (this->getColour() == WHITE){ 
        // checking to see if pawn does not go out of bounds and if next spot (jump one forward) is empty
        int nextSpot = curI-1;
        if (nextSpot < board.size() && board[nextSpot][curJ] == nullptr) {
            moves.push_back(Move(curI, curJ, nextSpot, curJ));
        }

        // checking if the white pawn can attack a piece to the right
        int rightAttackI = curI-1;
        int rightAttackJ = curJ+1;
                
        // board[i+1] because u want to check the size of the next index row, but since its 8x8 probably dont need this,
        // all sizes of each row are the same
        if (rightAttackI < board.size() && rightAttackJ < board.size() && board[rightAttackI][rightAttackJ] != nullptr
        && board[rightAttackI][rightAttackJ]->getColour() == BLACK) {
            moves.push_back(Move(curI, curJ, rightAttackI, rightAttackJ));
        }

        // checking if the white pawn can attack a piece to the left
        int leftAttackI = curI-1;
        int leftAttackJ = curJ-1;

        if (leftAttackI < board.size() && leftAttackJ < board.size() && board[leftAttackI][leftAttackJ] != nullptr
        && board[leftAttackI][leftAttackJ]->getColour() == Colour::BLACK) {
            moves.push_back(Move(curI, curJ, leftAttackI, leftAttackJ));
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

        if (rightAttackI < 8 && rightAttackJ < 8 && board[rightAttackI][rightAttackJ] != nullptr
        && board[rightAttackI][rightAttackJ]->getColour() == WHITE) {
            moves.push_back(Move(curI, curJ, rightAttackI, rightAttackJ));
        }

        // checking if black pawn can attack a piece to the left
        int leftAttackI = curI+1;
        int leftAttackJ = curJ+1;

        if (leftAttackI < board.size() && leftAttackJ < 8 && board[leftAttackI][leftAttackJ] != nullptr
        && board[leftAttackI][leftAttackJ]->getColour() == Colour::WHITE) {
            moves.push_back(Move(curI, curJ, leftAttackI, leftAttackJ));
        }
    }  

    return moves;
};

Pawn::~Pawn() {};