#ifndef COMPUTERONE_H
#define COMPUTERONE_H

#include <vector>
#include "computer.h"
#include <memory>
#include <iostream>

using namespace std;

class ComputerOne : public Computer 
{
    public:
        ComputerOne(Colour colour) : Computer(colour) {}
        
        Move chooseMove(const  vector<vector<unique_ptr<Piece>>>& board) override {
            vector<Move> allMovesICanMake = findAllMovesICanMake(board);
            int randomNumber = std::rand() % allMovesICanMake.size();
            return allMovesICanMake.at(randomNumber);
        }
};

#endif

