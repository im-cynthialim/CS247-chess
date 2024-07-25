#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "enums.h"
#include "piece.h"
#include "move.h"

using namespace std;

class Player 
{
    Colour colour; 
    bool canCastle;

    protected: 
        Player (Colour colour, bool canCastle);

    public:
        vector<Move> findAllMoves (vector<vector<Piece>>);
        virtual Move chooseMove(vector<vector<Piece>>) = 0;
};


#endif

