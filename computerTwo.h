#ifndef COMPUTERTWO_H
#define COMPUTERTWO_H

#include <vector>
#include "computer.h"

using namespace std;

class ComputerTwo : public Computer 
{
    public:
        Move chooseMove(vector<vector<Piece*>>) override;
        ComputerTwo(Colour colour, bool canCastle) : Computer(colour, canCastle) {}
};


#endif

