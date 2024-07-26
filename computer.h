#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include "player.h"

using namespace std;

class Computer : public Player 
{

    //helper bois
    vector<Move> findAllMovesICanMake(vector<vector<Piece*>> board);
    vector<Move> findAllMovesOppCanMake(vector<vector<Piece*>> board);

    protected: 
    Computer(Colour colour) : Player(colour) {}

    public:
        
        vector<Move> findChecks(vector<vector<Piece*>> board);
        vector<Move> findCaptures(vector<vector<Piece*>> board);
        vector<Move> avoidCaptures(vector<vector<Piece*>> board);
        // virtual Move chooseMove(vector<vector<Piece*>>) = 0;
};

#endif

