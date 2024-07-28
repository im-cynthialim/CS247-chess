#include <vector>
#include <algorithm>
#include "enums.h"
#include "move.h"
#include "king.h"
#include "piece.h"
#include "pawn.h"
using namespace std;

// construct the pawn
Pawn::Pawn(Colour c, char piecetype): Piece::Piece{c, piecetype} {};

// used to check if whitePawns are in one of the fixed located spots (6,0), (6,1) ... (6,7)
bool Pawn::getWhiteSpots(int curI, int curJ) {
    if (curI == 6 && curJ == 0) {
        return true;
    } else if (curI == 6 && curJ == 1) {
        return true;
    } else if (curI == 6 && curJ == 2) {
        return true;
    } else if (curI == 6 && curJ == 3) {
        return true;
    } else if (curI == 6 && curJ == 4) {
        return true;
    } else if (curI == 6 && curJ == 5) {
        return true;
    } else if (curI == 6 && curJ == 6) {
        return true;
    } else if (curI == 6 && curJ == 7) {
        return true;
    } else {
        return false;
    }
}

// used to check if blackPawns are in one of the fixed located spots (1,0), (1,1) ... (1,7)
bool Pawn::getBlackSpots(int curI, int curJ) {
    if (curI == 1 && curJ == 0) {
        return true;
    } else if (curI == 1 && curJ == 1) {
        return true;
    } else if (curI == 1 && curJ == 2) {
        return true;
    } else if (curI == 1 && curJ == 3) {
        return true;
    } else if (curI == 1 && curJ == 4) {
        return true;
    } else if (curI == 1 && curJ == 5) {
        return true;
    } else if (curI == 1 && curJ == 6) {
        return true;
    } else if (curI == 1 && curJ == 7) {
        return true;
    } else {
        return false;
    }

}

vector<Move> Pawn::lineOfSight(vector<vector<Piece*>> &board, int curI, int curJ) {
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

        // check if a pawn can move upwards twice
        // check to see if curI, curJ is a pawn and check to see if its in a specific spot
        // no need to check if out of bounds because the jump two up can never go out of bounds
        int moveTwoUpI = curI-2;
        bool twoUp = getWhiteSpots(curI, curJ);
        if (board[curI][curJ] == this && twoUp) {
            moves.push_back(Move(curI, curJ, moveTwoUpI, curJ));

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

        int moveTwoUp = curI+2;
        bool twoUp = getBlackSpots(curI, curJ);
        if (board[curI][curJ] == this && twoUp) {
            moves.push_back(Move(curI, curJ, moveTwoUp, curJ));
        }
    }  

    return moves;
};

vector<Move> Pawn::possibleMoves(vector<vector<Piece*>> &board, int row, int col) {
    vector<Move> validMoves{};
    vector<Move> potentialMoves = lineOfSight(board, row, col);  //get general moves of a pieces

    bool inCheck = false;
    int initX = row;
    int initY = col;
    int kingX, kingY;

    // find curPlayer king's position

    for (size_t Krow = 0; Krow < board.size(); ++Krow) {
        for (size_t Kcol = 0; Kcol < board[row].size(); ++Kcol) {
            if (board[Krow][Kcol] != nullptr && dynamic_cast<King*>(board.at(Krow).at(Kcol)) && board[Krow][Kcol]->getColour() == this->getColour()) { 
                kingX = Krow;
                kingY = Kcol;
                break;
                }
        }
    }

    // for each general move, call line of Sight on enemy pieces + see if my king within results (i.e. check) 
    int validateMove = 0; // index to iterate through generalMoves
    
    vector<vector<Piece*>> simulateBoard = board;

    while (validateMove < potentialMoves.size()) {
        simulateBoard[initX][initY] = nullptr;
        simulateBoard[potentialMoves[validateMove].getToX()][potentialMoves[validateMove].getToY()] = this; // put pawn in new potential place
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (simulateBoard[i][j] != nullptr && simulateBoard[i][j]->getColour() != this->getColour()) {

                    vector<Move> enemyMoves = simulateBoard.at(i).at(j)->getLineOfSightMoves(simulateBoard, i, j);
                    Move myKing = {i, j, kingX, kingY};
                    auto it = find (enemyMoves.begin(), enemyMoves.end(), myKing);
                    if (it != enemyMoves.end()) { // enemy piece checks my king
                        inCheck = true;
                        break; // general move is invalid
                    }
                }
            }
        }
        if (!inCheck) { // no enemy line of sight puts my king in check for my simulated move, therefore valid move
            validMoves.push_back(potentialMoves[validateMove]);
        }
        inCheck = false;
        initX = potentialMoves[validateMove].getToX();
        initY = potentialMoves[validateMove].getToY();
        ++validateMove;
    }

    return validMoves;
}

Pawn::~Pawn() {};