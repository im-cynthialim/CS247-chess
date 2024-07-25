#ifndef COMPUTERTHREE_H
#define COMPUTERTHREE_H

#include <vector>
#include "computer.h"

using namespace std;

class ComputerThree : public Computer 
{
    public:
        Move chooseMove(vector<vector<Piece>>) override;
        ComputerThree(Colour colour, bool canCastle) : Computer(colour, canCastle) {}
};


#endif

