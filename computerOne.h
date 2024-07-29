#ifndef COMPUTERONE_H
#define COMPUTERONE_H

#include <vector>
#include "computer.h"
#include <iostream>

using namespace std;

class ComputerOne : public Computer 
{
    public:
        ComputerOne(Colour colour) : Computer(colour) {}
        
        Move chooseMove(const vector<vector<Piece*>>& board) override {
            vector<Move> allMovesICanMake = findAllMovesICanMake(board);
            int randomNumber = std::rand() % allMovesICanMake.size();
            for (int i = 0; i < allMovesICanMake.size(); ++i) {
            allMovesICanMake.at(i).getFields();
            }
            return allMovesICanMake.at(randomNumber);
        }
};

#endif

