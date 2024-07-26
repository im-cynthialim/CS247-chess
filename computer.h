#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include "player.h"

using namespace std;

class Computer : public Player 
{

    //helper bois
    vector<Move> findAllMovesOppCanMake(const vector<vector<Piece*>>& board);

    protected: 
    Computer(Colour colour) : Player(colour) {}

    public:
        vector<Move> findChecks(const vector<vector<Piece*>>& board);
        vector<Move> findCaptures(const vector<vector<Piece*>>& board);
        vector<Move> avoidCaptures(const vector<vector<Piece*>>& board);
        virtual Move chooseMove(const vector<vector<Piece*>>& board) = 0;
};

#endif

