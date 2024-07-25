#ifndef COMPUTERONE_H
#define COMPUTERONE_H

#include <vector>
#include "computer.h"

using namespace std;

class ComputerOne : public Computer 
{
    public:
        virtual Move chooseMove(vector<vector<Piece>>) = 0;
};


#endif

