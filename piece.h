#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "enums.h"
#include "move.h"
#include "helperFuncs.h"
#include <cctype>

using namespace std;

class Piece {
    Colour colour;
    char pieceType;
    
    virtual vector<Move> possibleMoves(const vector<vector<Piece*>>& board, int row, int col) {
           vector<Move> validMoves{};
            vector<Move> potentialMoves = lineOfSight(board, row, col);  //get general moves of a pieces

            int kingX, kingY;
            // find curPlayer king's position
            for (size_t Krow = 0; Krow < board.size(); ++Krow) {
                for (size_t Kcol = 0; Kcol < board[row].size(); ++Kcol) {
                    if (board[Krow][Kcol] != nullptr && tolower(board[Krow][Kcol]->getPieceType()) == 'k' && board[Krow][Kcol]->getColour() == this->getColour()) { 
                        kingX = Krow;
                        kingY = Kcol;
                        break;
                        }
                }
            }

            for(int i = 0; i < potentialMoves.size(); i++) {
                vector<vector<Piece*>> simulateBoard = board;
                simulateBoard[row][col] = nullptr;
                simulateBoard[potentialMoves[i].getToX()][potentialMoves[i].getToY()] = this; // put king in new potential place
                if (!isKingInCheck(board[kingX][kingY]->getPieceType(), simulateBoard)) { // no enemy line of sight puts my king in check for my simulated move, therefore valid move
                    validMoves.push_back(potentialMoves[i]);
                }
            }

            return validMoves;
    };
    
    virtual vector<Move> lineOfSight(const vector<vector<Piece*>> &, int, int) = 0;
    
    public:
        bool hasMoved = false;
        Piece (Colour colour, char pieceType);
        char getPieceType();
        Colour getColour();
        vector<Move> getPossibleMoves (const vector<vector<Piece*>> &, int, int);
        vector<Move> getLineOfSightMoves(const vector<vector<Piece*>> &, int, int);
        virtual ~Piece();
};

#endif