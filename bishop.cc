#include <vector>
#include "bishop.h"
#include "enums.h"
#include "game.h"
#include "move.h"
#include "piece.h"

using namespace std;

// construct bishop
Bishop::Bishop(Colour c, char piecetype): Piece::Piece{c, piecetype} {};

vector<Move> Bishop::possibleMoves(vector<vector<Piece*>> board, int curI, int curJ) {
    vector<Move> moves;
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

    return moves;
}

Bishop::~Bishop() {}
