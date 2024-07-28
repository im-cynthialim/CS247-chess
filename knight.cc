#include "knight.h"
#include "king.h"
#include "piece.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

Knight::Knight(Colour c, char PieceType): Piece::Piece{c, PieceType} {};

vector<Move> Knight::lineOfSight(const vector<vector<Piece*>>& board, int row, int col) {

    vector<Move> validMoves {};

    // //counter clockwise motion
    // //up 2, 1 right - upper bound not added
    // if (row - 2 >= 0 && col + 1 < 8 && (board.at(row-2).at(col+1) == nullptr || board.at(row-2).at(col+1)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
    //     validMoves.push_back(Move{row, col, row-2, col+1});
    // }
    
    // //up 1, right 2
    // if (row - 1 >= 0 && col + 2 < 8 && (board.at(row-1).at(col+2) == nullptr || board.at(row-1).at(col+2)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
    //     validMoves.push_back(Move{row, col, row-1, col+2});
    // }

    // //down 1, right 2
    // if (row + 1 < 8 && col + 2 < 8 && (board.at(row+1).at(col+2) == nullptr || board.at(row+1).at(col+2)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
    //     validMoves.push_back(Move{row, col, row+1, col+2});
    // }

    // //down 2, right 1
    // if (row + 2 < 8 && col + 1 < 8 && (board.at(row+2).at(col+1) == nullptr || board.at(row+2).at(col+1)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
    //     validMoves.push_back(Move{row, col, row+2, col+1});
    // }

    // //down 2, left 1
    // if (row + 2 < 8 && col - 1 >= 0 && (board.at(row+2).at(col-1) == nullptr || board.at(row+2).at(col-1)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
    //     validMoves.push_back(Move{row, col, row+2, col-1});
    // }

    // //down 1, left 2
    // if (row + 1 < 8 && col - 2 >= 0 && (board.at(row+1).at(col-2) == nullptr || board.at(row+1).at(col-2)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
    //     validMoves.push_back(Move{row, col, row+1, col-2});
    // }

    // //up 1, left 2
    // if (row - 1 >=0 && col - 2 >= 0 && (board.at(row-1).at(col-2) == nullptr || board.at(row-1).at(col-2)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
    //     validMoves.push_back(Move{row, col, row-1, col-2});
    // }

    // //up 2, left 1
    // if (row - 2 >=0 && col - 1 >= 0 && (board.at(row-2).at(col-1) == nullptr || board.at(row-2).at(col-1)->getColour() != this->getColour())) { // if valid square + non empty + not same colour
    //     validMoves.push_back(Move{row, col, row-2, col-1});
    // }

    return validMoves;
}

vector<Move> Knight::possibleMoves(const vector<vector<Piece*>> &board, int row, int col) {
    vector<Move> validMoves{};
    vector<Move> potentialMoves = lineOfSight(board, row, col);  //get general moves of a pieces

    // call find king to find MY king's position
    int kingX = 3;
    int kingY = 6;
    bool inCheck = false;
    int initX = row;
    int initY = col;

    // for each general move, call line of Sight on enemy pieces + see if my king within results (i.e. check) 
    int validateMove = 0; // index to iterate through generalMoves
    
    vector<vector<Piece*>> simulateBoard = board;

    while (validateMove < potentialMoves.size()) {
        simulateBoard[initX][initY] = nullptr;
        simulateBoard[potentialMoves[validateMove].getToX()][potentialMoves[validateMove].getToY()] = this; // put knight in new potential place
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

Knight::~Knight() {}