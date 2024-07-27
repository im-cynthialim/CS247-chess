#include "rook.h"
#include "king.h"
#include "piece.h"
#include <iostream>
#include <memory>

Rook::Rook(Colour c, char PieceType): Piece::Piece{c, PieceType} {};

vector<Move> Rook::lineOfSight(vector<vector<Piece*>> &board, int row, int col) { // return all general valid moves (empty squares or captures)
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

vector<Move> Rook::possibleMoves(vector<vector<Piece*>> &board, int row, int col) {
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
    // delete simulateBoard[row][col];
    // simulateBoard[row][col] = nullptr;
    // simulateBoard[potentialMoves[validateMove].getToX()][potentialMoves[validateMove].getToY()]; // put rook in new potential place

    while (validateMove < potentialMoves.size()) {
        simulateBoard[initX][initY] = nullptr;
        simulateBoard[potentialMoves[validateMove].getToX()][potentialMoves[validateMove].getToY()] = this; // put rook in new potential place

        for (int i =0; i < simulateBoard.size(); ++i) {

            // for (int j = 0;j < 8;++j) {
            //     if (simulateBoard[i][j] != nullptr)
            //         cout << simulateBoard[i][j]->getPieceType();
            //     else {cout << "_";}
                
            // }
            // cout << "\n";
        }
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (simulateBoard[i][j] != nullptr && simulateBoard[i][j]->getColour() != this->getColour()) {

                    vector<Move> enemyMoves = simulateBoard.at(i).at(j)->getLineOfSightMoves(simulateBoard, i, j);

                    // cout << "--------ENEMY MOVES-------------" << "\n";
                    // for (int rand = 0; rand < enemyMoves.size(); ++rand) {
                    //     enemyMoves[rand].getFields();
                    // }
                    // cout << "--------END ENEMY MOVES-------------" << "\n";
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

Rook::~Rook() {};