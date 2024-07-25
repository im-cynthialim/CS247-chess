#ifndef COMPUTERTHREE_H
#define COMPUTERTHREE_H

#include <vector>
#include "computer.h"

using namespace std;

class ComputerThree : public Computer 
{
    public:
        virtual Move chooseMove(vector<vector<Piece>>) = 0;
};


#endif

