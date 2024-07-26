#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "enums.h"
#include "piece.h"
#include "move.h"

using namespace std;

class Player 
{
    protected: 
        Colour colour; 
        bool canCastle = false;
        Player (Colour colour) : colour{colour} {};
    public:
        vector<Move> findAllMovesICanMake (const vector<vector<Piece*>>&board) {
            vector<Move> allMovesICanMake = {};
            for (size_t row = 0; row < board.size(); ++row) {
                for (size_t col = 0; col < board[row].size(); ++col) {
                    Piece* piece = board[row][col];
                    if(piece != nullptr && colour == piece->getColour())  {
                        std::vector<Move> additionalMoves = piece->listMoves(board, row, col);
                        allMovesICanMake.insert(allMovesICanMake.end(), additionalMoves.begin(), additionalMoves.end()); //append
                    }
                }
            }
        }
        virtual Move chooseMove(const vector<vector<Piece*>>& board) = 0;

        Colour getColour() {
            return colour;
        }
};


#endif

