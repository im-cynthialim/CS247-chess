#ifndef COMPUTERONE_H
#define COMPUTERONE_H

#include <vector>
#include "computer.h"

using namespace std;

class ComputerOne : public Computer 
{
    public:
        // Move chooseMove(vector<vector<Piece*>>) override;
        ComputerOne(Colour colour) : Computer(colour) {}
};


#endif

