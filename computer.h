#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include "player.h"
#include <memory>

using namespace std;

class Computer : public Player 
{

    protected: 
    Computer(Colour colour) : Player(colour) {}

    public:
        vector<Move> findCaptures(const  vector<vector<unique_ptr<Piece>>>& board);
        vector<Move> avoidCaptures(const  vector<vector<unique_ptr<Piece>>>& board);
        virtual Move chooseMove(const  vector<vector<unique_ptr<Piece>>>& board) = 0;
};

#endif

