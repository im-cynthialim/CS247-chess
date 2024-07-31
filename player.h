#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "enums.h"
#include "piece.h"
#include "move.h"
#include <iostream>
#include <memory>

using namespace std;

class Player 
{
    protected: 
        Colour colour; 
        Player (Colour colour) : colour{colour} {};
    public:         
        //helper bois
        vector<Move> findAllMovesOppCanMake(const  vector<vector<unique_ptr<Piece>>>& board) {
            vector<Move> allMovesOppCanMake = {};
            for (size_t row = 0; row < board.size(); ++row) {
                for (size_t col = 0; col < board[row].size(); ++col) {
                    // unique_ptr<Piece> piece = (board[row][col] == nullptr ? nullptr : board[row][col]->getCreateNew(board[row][col]->getColour(), board[row][col]->getPieceType()));
                    // Piece* piece = board[row][col].get();
                    if(board[row][col] != nullptr && colour != board[row][col]->getColour())  {
                        std::vector<Move> additionalMoves = board[row][col]->getPossibleMoves(board, row, col);
                        allMovesOppCanMake.insert(allMovesOppCanMake.end(), additionalMoves.begin(), additionalMoves.end()); //append
                    }
                }
            }
            return allMovesOppCanMake;
        }

        vector<Move> findAllMovesICanMake (const  vector<vector<unique_ptr<Piece>>>&board) {
            vector<Move> allMovesICanMake = {};
            for (size_t row = 0; row < board.size(); ++row) {
                for (size_t col = 0; col < board[row].size(); ++col) {
                    
                    // unique_ptr<Piece> piece = (board[row][col] == nullptr ? nullptr : board[row][col]->getCreateNew(board[row][col]->getColour(), board[row][col]->getPieceType()));
                    // Piece* piece = board[row][col].get();
                    if(board[row][col] != nullptr && colour == board[row][col]->getColour())  {
                        vector<Move> additionalMoves = board[row][col]->getPossibleMoves(board, row, col);
                        allMovesICanMake.insert(allMovesICanMake.end(), additionalMoves.begin(), additionalMoves.end()); //append
                    }
                }
            }
            return allMovesICanMake;
        }

        virtual Move chooseMove(const  vector<vector<unique_ptr<Piece>>>& board) = 0;

        vector<Move> findChecks(const  vector<vector<unique_ptr<Piece>>>& board) {
            //this method find all of the moves I can make that will put their king in check 
            char otherKing = 'K';
            if (colour == WHITE) {
                otherKing = 'k';
            }

            vector<Move> allCheckMoves = {};

            //For each of my possible moves, find whether the other king is in check from this move
            vector<Move> allMovesICanMake = findAllMovesICanMake(board);
            for (size_t i = 0; i < allMovesICanMake.size(); ++i) {
                //simulate the board if this move was made 
                  vector<vector<unique_ptr<Piece>>> boardCopy;
                for (size_t r = 0; r < board.size(); ++r)
                {
                    for (size_t c = 0; c < board[r].size(); ++c)
                    {
                        if (boardCopy[r][c] != nullptr) {
                            boardCopy[r][c] = board[r][c]->getCreateNew(board[r][c]->getColour(), board[r][c]->getPieceType());
                        }
                        else {
                            boardCopy[r][c] = nullptr;
                        }
                        // boardCopy[r][c] != nullptr ? board[r][c]->getCreateNew(board[r][c]->getColour(), board[r][c]->getPieceType()) : nullptr;
                    }
                }
                // std::vector<std::vector<Piece*>> boardCopy = board; 
                boardCopy[allMovesICanMake[i].getToX()][allMovesICanMake[i].getToY()] = move(boardCopy[allMovesICanMake[i].getFromX()][allMovesICanMake[i].getFromY()]);
                boardCopy[allMovesICanMake[i].getFromX()][allMovesICanMake[i].getFromY()] = nullptr;

                if(isKingInCheck(otherKing, boardCopy)) {
                    allCheckMoves.push_back(allMovesICanMake[i]);
                }
            }
            return allCheckMoves;
        }


        Colour getColour() {
            return colour;
        }

        virtual ~Player() {}
};


#endif


