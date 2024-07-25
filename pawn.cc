#include <vector>
#include "enums.h"
#include "game.h"
#include "move.h"
#include "piece.h"
#include "pawn.h"
using namespace std;

// construct the pawn
Pawn::Pawn(Colour c, char piecetype): Piece{c, piecetype} {};

vector<Move> Pawn::possibleMoves(vector<vector<Piece*>> board, int curI, int curJ) {
    // return an array of moves for the pawn
    vector<Move> moves;

    // iterate through board to find a pawn
    if (board[curI][curJ]->getPieceType() == 'P' && board[curI][curJ]->getColour() == Colour::WHITE) {
        // checking to see if pawn does not go out of bounds and if next spot (jump one forward) is empty
        int nextSpot = curJ-1;
        if (nextSpot < board.size() && board[curI][nextSpot]->getPieceType() == ' ') {
            moves.push_back(Move(curI, curJ, curI, nextSpot));
        }

        // checking if the white pawn can attack a piece to the right
        int rightAttackI = curI+1;
        int rightAttackJ = curJ-1;
                
        // board[i+1] because u want to check the size of the next index row, but since its 8x8 probably dont need this,
        // all sizes of each row are the same
        if (rightAttackI < board.size() && rightAttackJ < board.size() && board[rightAttackI][rightAttackJ]->getPieceType() != ' '
        && board[rightAttackI][rightAttackJ]->getColour() == Colour::BLACK) {
            moves.push_back(Move(curI, curJ, rightAttackI, rightAttackJ));
        }

        // checking if the white pawn can attack a piece to the left
        int leftAttackI = curI-1;
        int leftAttackJ = curJ-1;

        if (leftAttackI < board.size() && leftAttackJ < board.size() && board[leftAttackI][leftAttackJ]->getPieceType() != ' '
        && board[leftAttackI][leftAttackJ]->getColour() == Colour::BLACK) {
            moves.push_back(Move(curI, curJ, leftAttackI, leftAttackJ));
        }
    }
    // black
    if (board[curI][curJ]->getPieceType() == 'p' && board[curI][curJ]->getColour() == Colour::BLACK) {
        // this is for checking to see if the piece does not go out of bounds and if next spot (jump one forward) is empty
        int nextSpot = curJ+1;
                    
        if (nextSpot < board.size() && board[curI][nextSpot]->getPieceType() == ' ') {
            moves.push_back(Move(curI, curJ, curI, nextSpot));
        }

        // checking if a black pawn can attack a piece to the right
        int rightAttackI = curI-1;
        int rightAttackJ = curJ+1;

        if (rightAttackI < board.size() && rightAttackJ < board.size() && board[rightAttackI][rightAttackJ]->getPieceType() != ' '
        && board[rightAttackI][rightAttackJ]->getColour() == Colour::WHITE) {
            moves.push_back(Move(curI, curJ, rightAttackI, rightAttackJ));
        }

        // checking if black pawn can attack a piece to the left
        int leftAttackI = curI+1;
        int leftAttackJ = curJ+1;

        if (leftAttackI < board.size() && leftAttackJ < board.size() && board[leftAttackI][leftAttackJ]->getPieceType() != ' '
        && board[leftAttackI][leftAttackJ]->getColour() == Colour::WHITE) {
            moves.push_back(Move(curI, curJ, leftAttackI, leftAttackJ));
        }
    }  

    return moves;
};
