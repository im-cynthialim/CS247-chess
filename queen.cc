#include <vector>
#include "queen.h"
#include "enums.h"
#include "move.h"
#include "king.h"
#include "piece.h"

using namespace std;


Queen::Queen(Colour c, char piecetype): Piece::Piece{c, piecetype} {};

vector<Move> Queen::lineOfSight(vector<vector<Piece*>> &board, int curI, int curJ) { 
    vector<Move> moves;
    // queen = bishop + rook
    // execute bishop diagonals

    int saveCurI = curI;
    int saveCurJ = curJ;
    int checkNextI = curI;
    int checkNextJ = curJ;

    // check white bishop, 3 cases, diagonal blank space, diagonal piece in its path, out of bounds diagonal

        // check diagonal left moves for white bishop, while loop to make sure its in bounds
        while (checkNextI < board.size() || checkNextJ < board.size()) {
            checkNextI -= 1;
            checkNextJ -= 1;

            // check if left diagonal is empty
            if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] == nullptr) {
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));
                // set (curI and curJ) = (checkNextI, checkNextJ)
                saveCurI = checkNextI;
                saveCurJ = checkNextJ;
            } else if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] != nullptr
            && board[checkNextI][checkNextJ]->getColour() != this->getColour()) {
                // check if left diagonal contains a piece in its path 
                // we can move to the spot with a piece, but stop checking spots after cause we cannot reach there
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));
                break;
            }
        }

        // reset checkNextI and checkNextJ for right diagonal checking
        saveCurI = curI;
        saveCurJ = curJ;
        checkNextI = curI;
        checkNextJ = curJ;

        // check diagonal right moves

        while (checkNextI < board.size() || checkNextJ < board.size()) {
            checkNextI -= 1;
            checkNextJ += 1;

            if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] == nullptr) {
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));

                saveCurI = checkNextI;
                saveCurJ = checkNextJ;
            } else if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] != nullptr
            && board[checkNextI][checkNextJ]->getColour() != this->getColour()) {
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));
                break;
            }
        }
    
        saveCurI = curI;
        saveCurJ = curJ;
        checkNextI = curI;
        checkNextJ = curJ;


        // check diagonal left moves for black bishop, while loop to make sure its in bounds
        while (checkNextI < board.size() || checkNextJ < board.size()) {
            checkNextI += 1;
            checkNextJ += 1;

            // check if left diagonal is empty
            if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] == nullptr) {
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));
                // set (curI and curJ) = (checkNextI, checkNextJ)
                saveCurI = checkNextI;
                saveCurJ = checkNextJ;
            } else if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] != nullptr
            && board[checkNextI][checkNextJ]->getColour() != this->getColour()) {
                // check if left diagonal contains a piece in its path 
                // we can move to the spot with a piece, but stop checking spots after cause we cannot reach there
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));
                break;
            }
        }

        // reset checkNextI and checkNextJ for right diagonal checking
        saveCurI = curI;
        saveCurJ = curJ;
        checkNextI = curI;
        checkNextJ = curJ;

        // check diagonal right moves

        while (checkNextI < board.size() || checkNextJ < board.size()) {
            checkNextI += 1;
            checkNextJ -= 1;

            if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] == nullptr) {
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));

                saveCurI = checkNextI;
                saveCurJ = checkNextJ;
            } else if (checkNextI < board.size() && checkNextJ < board.size() && board[checkNextI][checkNextJ] != nullptr
            && board[checkNextI][checkNextJ]->getColour() != this->getColour()) {
                moves.push_back(Move(saveCurI, saveCurJ, checkNextI, checkNextJ));
                break;
            }
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


vector<Move> Queen::possibleMoves(vector<vector<Piece*>> &board, int row, int col) {
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
        simulateBoard[potentialMoves[validateMove].getToX()][potentialMoves[validateMove].getToY()] = this; // put rook in new potential place
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
};

Queen::~Queen() {}