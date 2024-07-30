#include <vector>
#include <algorithm>
#include <iostream>
#include <cctype>
#include "piece.h"
#include "bishop.h"
#include "enums.h"
#include "king.h"
#include "move.h"
#include "helperFuncs.h"


using namespace std;

// construct bishop
Bishop::Bishop(Colour c, char piecetype): Piece::Piece{c, piecetype} {};

vector<Move> Bishop::lineOfSight(const vector<vector<Piece*>> &board, int curI, int curJ) {
    vector<Move> moves;

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
            } else if (board[checkNextI][checkNextJ] != nullptr
            && board[checkNextI][checkNextJ]->getColour() != this->getColour()) {
                moves.push_back(Move{curI, curJ, checkNextI, checkNextJ});
                break;
            }
               else {
                break;
            }
            ++checkNextI;
            --checkNextJ;
        } 
    return moves;
}

Bishop::~Bishop() {}
