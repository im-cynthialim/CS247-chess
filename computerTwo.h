#ifndef COMPUTERTWO_H
#define COMPUTERTWO_H

#include <vector>
#include "computer.h"

using namespace std;

class ComputerTwo : public Computer 
{
    public:
        virtual Move chooseMove(vector<vector<Piece>>) = 0;
};


#endif

