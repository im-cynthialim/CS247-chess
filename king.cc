#include <vector>
#include "enums.h"
#include "move.h"
#include "piece.h"
#include "king.h"
#include <algorithm>
#include <iostream>
#include "helperFuncs.h"
#include <cctype>
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

    //is this move going to cause the king to be in check? 
    for(int i = 0; i < potentialMoves.size(); i++) {
        vector<vector<Piece*>> simulateBoard = board;
        simulateBoard[row][col] = nullptr;
        simulateBoard[potentialMoves[i].getToX()][potentialMoves[i].getToY()] = this; // put king in new potential place
        if (!isKingInCheck(simulateBoard[potentialMoves[i].getToX()][potentialMoves[i].getToY()]->getPieceType(), simulateBoard)) { // no enemy line of sight puts my king in check for my simulated move, therefore valid move
            validMoves.push_back(potentialMoves[i]);
        }
    }


    //CASTLING
    //if the king is white: 
    std::pair<int, int> origKingPos(7, 4);
    std::pair<int, int> origRookClosestPos(7, 7);
    std::pair<int, int> origRookFarthestPos(7, 0);
    char rook = 'R';
    //if the king we are trying to see the moves of is black: 
    if(board[row][col]->getColour() == BLACK) {
        origKingPos = std::make_pair(0, 4);
        origRookClosestPos = std::make_pair(0, 7);
        origRookFarthestPos = std::make_pair(0, 0);
        rook = 'r';
    }

//______________________________________
    //CASTLING 
//______________________________________

    //1)king cant be currently in check?
    //2)king cant have moved?
    if(origKingPos.first != row || origKingPos.second != col || (board[row][col]== nullptr) || isKingInCheck(board[row][col]->getPieceType(), board) || this->hasMoved || origKingPos.first != row || origKingPos.second != col) {
        return validMoves;
    }
    
    //CASTLING CLOSEST TO KING
    //3)rook right of king cant have moved?
    bool hasRookClosestMoved = true;
    if(board[origRookClosestPos.first][origRookClosestPos.second] != nullptr && 
    board[origRookClosestPos.first][origRookClosestPos.second]->getPieceType() == rook && 
    board[origRookClosestPos.first][origRookClosestPos.second]->hasMoved == false
    ) {
        hasRookClosestMoved = false;
    }

    //4)is there a piece in the position one right of king
    //5)is there a piece in the position two right from king 

    //6)if the king is put one space over to the right, is it in check? (dont move rook)
    bool isKingOneRightChecked = false;
    vector<vector<Piece*>> simulateBoard = board;
    simulateBoard[row][col+1] = this;
    simulateBoard[row][col] = nullptr;
    if ((isKingInCheck(simulateBoard[row][col+1]->getPieceType(), simulateBoard))) {
        isKingOneRightChecked = true;
    }

    //7) if the king is moved two spaces over to the right, is it in check? (dont move rook)
    bool isKingTwoRightChecked = false;
    simulateBoard = board;
    simulateBoard[row][col+2] = this;
    simulateBoard[row][col] = nullptr;
    if ((isKingInCheck(simulateBoard[row][col+2]->getPieceType(), simulateBoard))) {
        isKingTwoRightChecked = true;
    }

    if (
        !hasRookClosestMoved && //rook closest hasn't move
        board[origKingPos.first][origKingPos.second + 1] == nullptr && //no piece next to king on right
        board[origKingPos.first][origKingPos.second + 2] == nullptr && //no piece to right of the king
        !isKingOneRightChecked && 
        !isKingTwoRightChecked
    ) {
        validMoves.push_back(Move{row, col, row, col+2}); //add castle closest
    }

    //CASTLING FARTHEST TO KING
    //rook left of king cant have moved?
    bool hasRookFarthestMoved = true;
    if(board[origRookFarthestPos.first][origRookFarthestPos.second] != nullptr && 
    board[origRookFarthestPos.first][origRookFarthestPos.second]->getPieceType() == rook && 
    board[origRookFarthestPos.first][origRookFarthestPos.second]->hasMoved == false
    ) {
        hasRookFarthestMoved = false;
    }

    //is there a piece in the position one left of king
    //is there a piece in the position two left from king 
    //is there a piece in the position three left from king 
    
    //if the king is put one space over to the left, is it in check? (dont move rook)
    bool isKingOneLeftChecked = false;
    simulateBoard = board;
    simulateBoard[row][col-1] = this;
    simulateBoard[row][col] = nullptr;
    if ((isKingInCheck(simulateBoard[row][col-1]->getPieceType(), simulateBoard))) {
        isKingOneLeftChecked = true;
    }

    //if the king is moved two spaces over to the right, is it in check? (dont move rook)
    bool isKingTwoLeftChecked = false;
    simulateBoard = board;
    simulateBoard[row][col-2] = this;
    simulateBoard[row][col] = nullptr;
    if ((isKingInCheck(simulateBoard[row][col-2]->getPieceType(), simulateBoard))) {
        isKingTwoLeftChecked = true;
    }

    //if the king is moved two spaces over to the right, is it in check? (dont move rook)
    bool isKingThreeLeftChecked = false;
    simulateBoard = board;
    simulateBoard[row][col-3] = this;
    simulateBoard[row][col] = nullptr;
    if ((isKingInCheck(simulateBoard[row][col-3]->getPieceType(), simulateBoard))) {
        isKingThreeLeftChecked = true;
    }

    //add castle farthest to me
    if (
        !hasRookFarthestMoved && //rook farthest hasn't move
        board[origKingPos.first][origKingPos.second - 1] == nullptr && //no piece next to king on left
        board[origKingPos.first][origKingPos.second - 2] == nullptr && //no piece two left of the king
        board[origKingPos.first][origKingPos.second - 3] == nullptr && //no piece two left of the king
        !isKingOneLeftChecked && 
        !isKingTwoLeftChecked &&
        !isKingThreeLeftChecked
    ) {
        validMoves.push_back(Move{row, col, row, col-2});
    }

    return validMoves;
};

King::~King() {}
