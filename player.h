#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "enums.h"
#include "piece.h"
#include "move.h"
#include <iostream>

using namespace std;

class Player 
{
    protected: 
        Colour colour; 
        Player (Colour colour) : colour{colour} {};
    public:         
        //helper bois
        vector<Move> findAllMovesOppCanMake(const vector<vector<Piece*>>& board) {
            vector<Move> allMovesOppCanMake = {};
            for (size_t row = 0; row < board.size(); ++row) {
                for (size_t col = 0; col < board[row].size(); ++col) {
                    Piece* piece = board[row][col];
                    if(piece != nullptr && colour != piece->getColour())  {
                        std::vector<Move> additionalMoves = piece->getPossibleMoves(board, row, col);
                        allMovesOppCanMake.insert(allMovesOppCanMake.end(), additionalMoves.begin(), additionalMoves.end()); //append
                    }
                }
            }
            return allMovesOppCanMake;
        }

        vector<Move> findAllMovesICanMake (const vector<vector<Piece*>>&board) {
            vector<Move> allMovesICanMake = {};
            for (size_t row = 0; row < board.size(); ++row) {
                for (size_t col = 0; col < board[row].size(); ++col) {
                    Piece* piece = board[row][col];
                    if(piece != nullptr && colour == piece->getColour())  {
                        vector<Move> additionalMoves = piece->getPossibleMoves(board, row, col);
                        allMovesICanMake.insert(allMovesICanMake.end(), additionalMoves.begin(), additionalMoves.end()); //append
                    }
                }
            }
            return allMovesICanMake;
        }

        virtual Move chooseMove(const vector<vector<Piece*>>& board) = 0;

        vector<Move> findChecks(const vector<vector<Piece*>>& board) {
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
                std::vector<std::vector<Piece*>> boardCopy = board; 
                boardCopy[allMovesICanMake[i].getToX()][allMovesICanMake[i].getToY()] = boardCopy[allMovesICanMake[i].getFromX()][allMovesICanMake[i].getFromY()]; //simulate moving the piece over
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


