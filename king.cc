#include <vector>
#include "enums.h"
#include "move.h"
#include "piece.h"
#include "king.h"
#include <algorithm>
#include <iostream>
using namespace std;

// construct King object
King::King(Colour c, char pieceType): Piece{c, pieceType} {}



vector<Move> King::lineOfSight(const vector<vector<Piece*>> &board, int curI, int curJ) {

    vector<Move> moves = {};
    // // check all 8 scenarios
    int saveCurI = curI;
    int saveCurJ = curJ;

    // top left, check out of bounds, empty, or theres a piece and piece's colour is not itself
    curI -= 1;
    curJ -= 1;
    if (curI >= 0 && curJ >= 0 && (board[curI][curJ] == nullptr
    || (board[curI][curJ] != nullptr && board[curI][curJ]->getColour() != this->getColour()))) {
        moves.push_back(Move(saveCurI, saveCurJ, curI, curJ));
    }

    // reset to be the start values
    curI = saveCurI;
    curJ = saveCurJ;

    // top mid
    curI -= 1;
    if (curI >= 0 && curJ < board.size() && (board[curI][curJ] == nullptr 
    || (board[curI][curJ] != nullptr && board[curI][curJ]->getColour() != this->getColour()))) {
        moves.push_back(Move(saveCurI, saveCurJ, curI, curJ));
    }

    // reset to be the start values
    curI = saveCurI;
    curJ = saveCurJ;

    // top right
    curI -= 1;
    curJ += 1;
    if (curI >= 0 && curJ < board.size() && (board[curI][curJ] == nullptr
    || (board[curI][curJ] != nullptr && board[curI][curJ]->getColour() != this->getColour()))) {
        moves.push_back(Move(saveCurI, saveCurJ, curI, curJ));
    }

     // reset to be the start values
    curI = saveCurI;
    curJ = saveCurJ;

    // right
    curJ += 1;
    if (curI < board.size() && curJ < board.size() && (board[curI][curJ] == nullptr
    || (board[curI][curJ] != nullptr && board[curI][curJ]->getColour() != this->getColour()))) {
        moves.push_back(Move(saveCurI, saveCurJ, curI, curJ));
    }

     // reset to be the start values
    curI = saveCurI;
    curJ = saveCurJ;

    // bottom right
    curI += 1;
    curJ += 1;
    if (curI < board.size() && curJ < board.size() && (board[curI][curJ] == nullptr
    || (board[curI][curJ] != nullptr && board[curI][curJ]->getColour() != this->getColour()))) {
        moves.push_back(Move(saveCurI, saveCurJ, curI, curJ));
    }

    // reset to be the start values
    curI = saveCurI;
    curJ = saveCurJ;

    // bottom mid
    curI += 1;
    if (curI < board.size() && curJ < board.size() && (board[curI][curJ] == nullptr
    || (board[curI][curJ] != nullptr && board[curI][curJ]->getColour() != this->getColour()))) {
        moves.push_back(Move(saveCurI, saveCurJ, curI, curJ));
    }

    // reset to be the start values
    curI = saveCurI;
    curJ = saveCurJ;

    // bottom left
    curI += 1;
    curJ -= 1;
    if (curI < board.size() && curJ >= 0 && (board[curI][curJ] == nullptr
    || (board[curI][curJ] != nullptr && board[curI][curJ]->getColour() != this->getColour()))) {
        moves.push_back(Move(saveCurI, saveCurJ, curI, curJ));
    }

    // reset to be the start values
    curI = saveCurI;
    curJ = saveCurJ;

    // left
    curJ -= 1;
    if (curI < board.size() && curJ >= 0 && (board[curI][curJ] == nullptr
    || (board[curI][curJ] != nullptr && board[curI][curJ]->getColour() != this->getColour()))) {
        moves.push_back(Move(saveCurI, saveCurJ, curI, curJ));
    }

    return moves;
}

vector<Move> King::possibleMoves(const vector<vector<Piece*>> &board, int row, int col) {
    vector<Move> validMoves{};
    vector<Move> potentialMoves = lineOfSight(board, row, col);  //get general moves of a pieces

    bool inCheck = false;
    int initX = row;
    int initY = col;

    // for each general move, call line of Sight on enemy pieces + see if my king within results (i.e. check) 
    int validateMove = 0; // index to iterate through generalMoves
    
    vector<vector<Piece*>> simulateBoard = board;

    while (validateMove < potentialMoves.size()) {
        simulateBoard[initX][initY] = nullptr;
        simulateBoard[potentialMoves[validateMove].getToX()][potentialMoves[validateMove].getToY()] = this; // put king in new potential place

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (simulateBoard[i][j] != nullptr && simulateBoard[i][j]->getColour() != this->getColour()) {

                    vector<Move> enemyMoves = simulateBoard.at(i).at(j)->getLineOfSightMoves(simulateBoard, i, j);
                    Move myKing = {i, j, potentialMoves[validateMove].getToX(), potentialMoves[validateMove].getToY()};
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
};

King::~King() {}