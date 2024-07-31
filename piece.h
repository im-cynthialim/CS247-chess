#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "enums.h"
#include "move.h"
#include "helperFuncs.h"
#include <cctype>
#include <memory>

using namespace std;

class Piece
{
    Colour colour;
    char pieceType;

    virtual vector<Move> possibleMoves(const vector<vector<unique_ptr<Piece>>> &board, int row, int col)
    {
        vector<Move> validMoves{};
        vector<Move> potentialMoves = this->lineOfSight(board, row, col); // get general moves of a pieces

        int kingX, kingY;
        // find curPlayer king's position
        for (int Krow = 0; Krow < board.size(); ++Krow)
        {
            for (int Kcol = 0; Kcol < board[row].size(); ++Kcol)
            {
                if (board[Krow][Kcol] != nullptr && tolower(board[Krow][Kcol]->getPieceType()) == 'k' && board[Krow][Kcol]->getColour() == this->getColour())
                {
                    kingX = Krow;
                    kingY = Kcol;
                    break;
                }
            }
        }

        // for (int i = 0; i < potentialMoves.size(); i++)
        // {
        //     vector<vector<unique_ptr<Piece>>> simulateBoard;
        //     for (int r = 0; r < 8; ++r)
        //     {
        //         for (size_t c = 0; c < 8; ++c)
        //         {
        //             //  if (simulateBoard[r][c] != nullptr) {
        //             //         simulateBoard[r][c] = board[r][c]->getCreateNew(board[r][c]->getColour(), board[r][c]->getPieceType());
        //             //     }
        //             //     else {
        //                     simulateBoard[r][c] = nullptr;
        //                 // }
        //         }
        //     }
        //     // simulateBoard[row][col] = nullptr;
        //     // simulateBoard[potentialMoves[i].getToX()][potentialMoves[i].getToY()] = this->getCreateNew(this->getColour(), this->getPieceType()); // put king in new potential place
        //     // if (!isKingInCheck(board[kingX][kingY]->getPieceType(), simulateBoard))
        //     // { // no enemy line of sight puts my king in check for my simulated move, therefore valid move
        //     //     validMoves.push_back(potentialMoves[i]);
        //     // }
        // }

        return validMoves;
    };

    virtual vector<Move> lineOfSight(const vector<vector<unique_ptr<Piece>>> &board, int, int) = 0;
    virtual unique_ptr<Piece> createNew(Colour colour, char pieceType) = 0;
    

public:
    unique_ptr<Piece> getCreateNew(Colour colour, char pieceType);
    bool hasMoved = false;
    Piece(Colour colour, char pieceType);
    char getPieceType();
    Colour getColour();
    vector<Move> getPossibleMoves(const vector<vector<unique_ptr<Piece>>> &, int, int);
    vector<Move> getLineOfSightMoves(const vector<vector<unique_ptr<Piece>>> &, int, int);
    virtual ~Piece();
};

#endif
