#include <vector>
#include <algorithm>
#include "queen.h"
#include "enums.h"
#include "move.h"
#include <iostream>
#include "king.h"
#include <cctype>
#include "piece.h"
#include "helperFuncs.h"

using namespace std;


Queen::Queen(Colour c, char piecetype): Piece::Piece{c, piecetype} {};

vector<Move> Queen::lineOfSight(const vector<vector<Piece*>> &board, int curI, int curJ) { 
    vector<Move> moves = {};
    // // queen = bishop + rook
    // execute bishop diagonals
    
    int checkNextI = curI - 1;
    int checkNextJ = curJ - 1;


        // check up + left diagonal
        while (checkNextI >= 0 && checkNextJ >= 0) {
            // check if left diagonal is empty
            if (board[checkNextI][checkNextJ] == nullptr) {
                moves.push_back(Move{curI, curJ, checkNextI, checkNextJ});
            } else if (board[checkNextI][checkNextJ] != nullptr && board[checkNextI][checkNextJ]->getColour() != this->getColour()) {
                // check if left diagonal contains a piece in its path 
                // we can move to the spot with a piece, but stop checking spots after cause we cannot reach there
                moves.push_back(Move{curI, curJ, checkNextI, checkNextJ});
                break;
            }
            else {
                break;
            }
            --checkNextI;
            --checkNextJ;
        }

        // reset checkNextI and checkNextJ for right diagonal checking
        checkNextI = curI - 1;
        checkNextJ = curJ + 1;

        // check diagonal right moves

        while (checkNextI < board.size() && checkNextI >= 0 && checkNextJ < board.size()) {

            if (checkNextI < board.size() && checkNextI >= 0 && checkNextJ < board.size() && board[checkNextI][checkNextJ] == nullptr) {
                moves.push_back(Move{curI, curJ, checkNextI, checkNextJ});

                // saveCurI = checkNextI;
                // saveCurJ = checkNextJ;
            } else if (checkNextI < board.size() && checkNextI >= 0 && checkNextJ < board.size() && board[checkNextI][checkNextJ] != nullptr
            && board[checkNextI][checkNextJ]->getColour() != this->getColour()) {
                moves.push_back(Move{curI, curJ, checkNextI, checkNextJ});
                break;
            }
               else {
                break;
            }
            --checkNextI;
            ++checkNextJ;   
        }
    
        checkNextI = curI + 1;
        checkNextJ = curJ + 1;


       // check right bottom diagonal
        while (checkNextI < board.size() && checkNextJ < board.size()) {

            // check if left diagonal is empty
            if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] == nullptr) {
                moves.push_back(Move{curI, curJ, checkNextI, checkNextJ});
                // set (curI and curJ) = (checkNextI, checkNextJ)
                // saveCurI = checkNextI;
                // saveCurJ = checkNextJ;
            } else if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] != nullptr
            && board[checkNextI][checkNextJ]->getColour() != this->getColour()) {
                // check if left diagonal contains a piece in its path 
                // we can move to the spot with a piece, but stop checking spots after cause we cannot reach there
                moves.push_back(Move{curI, curJ, checkNextI, checkNextJ});
                break;
            }
               else {
                break;
            }
            ++checkNextI;
            ++checkNextJ;
        }

        // reset checkNextI and checkNextJ for right diagonal checking

        checkNextI = curI + 1;
        checkNextJ = curJ - 1;

        // check bottom left moves

        while (checkNextI < board.size() && checkNextJ < board.size() && checkNextJ >= 0) {
            if (checkNextI < board.size() && checkNextJ < board.size() && checkNextJ >= 0 && board[checkNextI][checkNextJ] == nullptr) {
                moves.push_back(Move{curI, curJ, checkNextI, checkNextJ});

                // saveCurI = checkNextI;
                // saveCurJ = checkNextJ;
            } else if (checkNextI < board.size() && checkNextJ < board.size() && checkNextJ >= 0 && board[checkNextI][checkNextJ] != nullptr
            && board[checkNextI][checkNextJ]->getColour() != this->getColour()) {
                moves.push_back(Move{curI, curJ, checkNextI, checkNextJ});
            }
               else {
                break;
            }
            ++checkNextI;
            --checkNextJ;
        } 


    // execute rook hor + vert

    int i = curI + 1;
    //vertical
    while (i < 8) { // move down
        if(board.at(i).at(curJ) == nullptr) { // empty square
            moves.push_back(Move{curI, curJ, i, curJ});
        }
        else if (board.at(i).at(curJ)->getColour() != this->getColour()) { // different colour means capture, can't move beyond
            moves.push_back(Move{curI, curJ, i, curJ});
            break;
        }
        else { // same colour at square
            break;
        }
        ++i;
    }

    // move up 
    i = curI - 1;

    while (i >= 0) { 
         if(board.at(i).at(curJ) == nullptr) { // empty square
            moves.push_back(Move{curI, curJ, i, curJ});
        }
        else if (board.at(i).at(curJ)->getColour() != this->getColour()) { // different colour means capture, can't move beyond
            moves.push_back(Move{curI, curJ, i, curJ});
            break;
        }
        else { // same colour at square
            break;
        }
        --i;
    }

    //check horizontal moves
    int j = curJ + 1;

    while (j < 8) { //check top/bottom moves (depends on colour)
        if(board.at(curI).at(j) == nullptr) { // empty square
        moves.push_back(Move{curI, curJ, curI, j});
    }
    else if (board.at(curI).at(j)->getColour() != this->getColour()) { // different colour means capture, can't move beyond
        moves.push_back(Move{curI, curJ, curI, j});
        break;
    }
    else { // same colour at square
        break;
    }
    ++j;
    }

    //check top/bottom moves (depends on colour)   

    j = curJ - 1;

    while (j >= 0) { 
        if(board.at(curI).at(j) == nullptr) { // empty square
        moves.push_back(Move{curI, curJ, curI, j});
    }
    else if (board.at(curI).at(j)->getColour() != this->getColour()) { // different colour means capture, can't move beyond
        moves.push_back(Move{curI, curJ, curI, j});
        break;
    }
    else { // same colour at square
        break;
    }
    --j;
    }
    return moves;
}


// vector<Move> Queen::possibleMoves(const vector<vector<Piece*>> &board, int row, int col) {
//     vector<Move> validMoves{};
//     vector<Move> potentialMoves = lineOfSight(board, row, col);  //get general moves of a pieces

//     int kingX, kingY;
//     // find curPlayer king's position
//     for (size_t Krow = 0; Krow < board.size(); ++Krow) {
//         for (size_t Kcol = 0; Kcol < board[row].size(); ++Kcol) {
//             if (board[Krow][Kcol] != nullptr && tolower(board[Krow][Kcol]->getPieceType()) == 'k' && board[Krow][Kcol]->getColour() == this->getColour()) { 
//                 kingX = Krow;
//                 kingY = Kcol;
//                 break;
//                 }
//         }
//     }

//     for(int i = 0; i < potentialMoves.size(); i++) {
//         vector<vector<Piece*>> simulateBoard = board;
//         simulateBoard[row][col] = nullptr;
//         simulateBoard[potentialMoves[i].getToX()][potentialMoves[i].getToY()] = this; // put king in new potential place
//         if (!isKingInCheck(board[kingX][kingY]->getPieceType(), simulateBoard)) { // no enemy line of sight puts my king in check for my simulated move, therefore valid move
//             validMoves.push_back(potentialMoves[i]);
//         }
//     }

//     return validMoves;
// };

Queen::~Queen() {}