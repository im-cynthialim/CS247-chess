#include <vector>
#include <algorithm>
#include "bishop.h"
#include "enums.h"
#include "king.h"
#include "move.h"
#include "piece.h"

using namespace std;

// construct bishop
Bishop::Bishop(Colour c, char piecetype): Piece::Piece{c, piecetype} {};

vector<Move> Bishop::lineOfSight(vector<vector<Piece*>> &board, int curI, int curJ) {
    vector<Move> moves;
    int saveCurI = curI;
    int saveCurJ = curJ;
    int checkNextI = curI - 1;
    int checkNextJ = curJ - 11;

    // check white bishop, 3 cases, diagonal blank space, diagonal piece in its path, out of bounds diagonal

        // check diagonal left moves for white bishop, while loop to make sure its in bounds
        while (checkNextI < board.size() || checkNextJ < board.size()) {

            // check if left diagonal is empty
            if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] == nullptr) {
                moves.push_back(Move(curI, curJ, checkNextI, checkNextJ));
                // set (curI and curJ) = (checkNextI, checkNextJ)
            } else if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] != nullptr
            && board[checkNextI][checkNextJ]->getColour() != this->getColour()) {
                // check if left diagonal contains a piece in its path 
                // we can move to the spot with a piece, but stop checking spots after cause we cannot reach there
                moves.push_back(Move(curI, curJ, checkNextI, checkNextJ));
                break;
            }
            --checkNextI;
            --checkNextJ;
        }

        // reset checkNextI and checkNextJ for right diagonal checking
        saveCurI = curI;
        saveCurJ = curJ;
        checkNextI = curI - 1;
        checkNextJ = curJ + 1;

        // check diagonal right moves

        while (checkNextI < board.size() || checkNextJ < board.size()) {

            if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] == nullptr) {
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));

                // saveCurI = checkNextI;
                // saveCurJ = checkNextJ;
            } else if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] != nullptr
            && board[checkNextI][checkNextJ]->getColour() != this->getColour()) {
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));
                break;
            }
            --checkNextI;
            ++checkNextJ;   
        }
    
        saveCurI = curI;
        saveCurJ = curJ;
        checkNextI = curI + 1;
        checkNextJ = curJ + 1;


        // check diagonal left moves for black bishop, while loop to make sure its in bounds
        while (checkNextI < board.size() || checkNextJ < board.size()) {

            // check if left diagonal is empty
            if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] == nullptr) {
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));
                // set (curI and curJ) = (checkNextI, checkNextJ)
                // saveCurI = checkNextI;
                // saveCurJ = checkNextJ;
            } else if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] != nullptr
            && board[checkNextI][checkNextJ]->getColour() != this->getColour()) {
                // check if left diagonal contains a piece in its path 
                // we can move to the spot with a piece, but stop checking spots after cause we cannot reach there
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));
                break;
            }
            ++checkNextI;
            ++checkNextJ;
        }

        // reset checkNextI and checkNextJ for right diagonal checking
        saveCurI = curI;
        saveCurJ = curJ;
        checkNextI = curI + 1;
        checkNextJ = curJ - 1;

        // check diagonal right moves

        while (checkNextI < board.size() || checkNextJ < board.size()) {

            if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] == nullptr) {
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));

                // saveCurI = checkNextI;
                // saveCurJ = checkNextJ;
            } else if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] != nullptr
            && board[checkNextI][checkNextJ]->getColour() != this->getColour()) {
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));
                break;
            }
            ++checkNextI;
            --checkNextJ;
        } 

    return moves;
}

vector<Move> Bishop::possibleMoves(vector<vector<Piece*>> &board, int row, int col) {
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
        simulateBoard[potentialMoves[validateMove].getToX()][potentialMoves[validateMove].getToY()] = this; // put bishop in new potential place
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



Bishop::~Bishop() {}
