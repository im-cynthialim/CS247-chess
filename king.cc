#include <vector>
#include "enums.h"
#include "move.h"
#include "piece.h"
#include "king.h"
using namespace std;

// construct King object
King::King(Colour c, char pieceType): Piece{c, pieceType} {}


vector<Move> King::possibleMoves(vector<vector<Piece*>> &board, int curI, int curJ) {};
vector<Move> King::lineOfSight(vector<vector<Piece*>> &board, int curI, int curJ) {

    vector<Move> moves;
    // check all 8 scenarios
    int saveCurI = curI;
    int saveCurJ = curJ;

    // top left, check out of bounds, empty, or theres a piece and piece's colour is not itself
    curI -= 1;
    curJ -= 1;
    if (curI < board.size() && curJ < board.size() && (board[curI][curJ] == nullptr
    || (board[curI][curJ] != nullptr && board[curI][curJ]->getColour() != this->getColour()))) {
        moves.push_back(Move(saveCurI, saveCurJ, curI, curJ));
    }

    // reset to be the start values
    curI = saveCurI;
    curJ = saveCurJ;

    // top mid
    curI -= 1;
    if (curI < board.size() && curJ < board.size() && (board[curI][curJ] == nullptr 
    || (board[curI][curJ] != nullptr && board[curI][curJ]->getColour() != this->getColour()))) {
        moves.push_back(Move(saveCurI, saveCurJ, curI, curJ));
    }

    // reset to be the start values
    curI = saveCurI;
    curJ = saveCurJ;

    // top right
    curI -= 1;
    curJ += 1;
    if (curI < board.size() && curJ < board.size() && (board[curI][curJ] == nullptr
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
    if (curI < board.size() && curJ < board.size() && (board[curI][curJ] == nullptr
    || (board[curI][curJ] != nullptr && board[curI][curJ]->getColour() != this->getColour()))) {
        moves.push_back(Move(saveCurI, saveCurJ, curI, curJ));
    }

    return moves;
}

King::~King() {}