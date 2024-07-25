#include <vector>
#include "enums.h"
#include "game.h"
#include "move.h"
#include "piece.h"
#include "pawn.h"
using namespace std;

// construct the pawn
Pawn::Pawn(Colour c, char piecetype): Piece(c, piecetype) {};

// getter for piecetype
char Piece::getPieceType() {
    return this->pieceType;
}

// getter for colour
Colour Piece::getColour() {
    return colour;
}

vector<Move> Pawn::possibleMoves(vector<vector<Piece>> board, int row, int col) {
    // return an array of moves for the pawn
    vector<Move> moves;

    // iterate through board to find a pawn
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            // might need to check that the position of P on the board matches the Pawn im calling on
            if (board[i][j].getPieceType() == 'P' && board[i][j].getColour() == Colour::WHITE) {
                // checking to see if pawn does not go out of bounds and if next spot (jump one forward) is empty
                int nextSpot = j-1;
                if (nextSpot < board.size() && board[i][nextSpot].getPieceType() == ' ') {
                    moves.push_back(Move(i, j, i, nextSpot));
                }

                // checking if the white pawn can attack a piece to the right
                int rightAttackI = i+1;
                int rightAttackJ = j-1;
                
                // board[i+1] because u want to check the size of the next index row, but since its 8x8 probably dont need this,
                // all sizes of each row are the same
                if (rightAttackI < board.size() && rightAttackJ < board.size() && board[rightAttackI][rightAttackJ].getPieceType() != ' ') {
                    moves.push_back(Move(i, j, rightAttackI, rightAttackJ));
                }

                // checking if the white pawn can attack a piece to the left
                int leftAttackI = i-1;
                int leftAttackJ = j-1;

                if (leftAttackI < board.size() && leftAttackJ < board.size() && board[leftAttackI][leftAttackJ].getPieceType() != ' ') {
                    moves.push_back(Move(i, j, leftAttackI, leftAttackJ));
                }
            }
            // black
            if (board[i][j].getPieceType() == 'P' && board[i][j].getColour() == Colour::BLACK) {
                // this is for checking to see if the piece does not go out of bounds and if next spot (jump one forward) is empty
                int nextSpot = j+1;
                    
                if (nextSpot < board.size() && board[i][nextSpot].getPieceType() == ' ') {
                    moves.push_back(Move(i, j, i, nextSpot));
                }

                // checking if a black pawn can attack a piece to the right
                int rightAttackI = i-1;
                int rightAttackJ = j+1;

                if (rightAttackI < board.size() && rightAttackJ < board.size() && board[rightAttackI][rightAttackJ].getPieceType() != ' ') {
                    moves.push_back(Move(i, j, rightAttackI, rightAttackJ));
                }

                // checking if black pawn can attack a piece to the left
                int leftAttackI = i+1;
                int leftAttackJ = j+1;

                if (leftAttackI < board.size() && leftAttackJ < board.size() && board[leftAttackI][leftAttackJ].getPieceType() != ' ') {
                    moves.push_back(Move(i, j, leftAttackI, leftAttackJ));

                }
             }
        }
    }
};
