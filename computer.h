#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include "player.h"

using namespace std;

class Computer : public Player 
{

    protected: 
    Computer(Colour colour, bool canCastle) : Player(colour, canCastle) {}

    public:
        
        vector<Move> findChecks(vector<vector<Piece>>);
        vector<Move> findCapture(vector<vector<Piece>>);
        vector<Move> avoidCaptures(vector<vector<Piece>>);
        virtual Move chooseMove(vector<vector<Piece>>) = 0;

    
};

#endif

