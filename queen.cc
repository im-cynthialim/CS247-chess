#include <vector>
#include "queen.h"
#include "enums.h"
#include "game.h"
#include "move.h"
#include "piece.h"

using namespace std;


Queen::Queen(Colour c, char piecetype): Piece::Piece{c, piecetype} {};

vector<Move> Queen::possibleMoves(vector<vector<Piece*>> board, int curI, int curJ) {
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
    //check horizontal moves 
    while (i < 8) { // moves on right side -->
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

    //check left side <--- 
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

    //check vertical moves
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

Queen::~Queen() {}