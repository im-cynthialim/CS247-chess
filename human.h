#ifndef HUMAN_H
#define HUMAN_H

#include <vector>
#include "player.h"

using namespace std;

class Human : public Player 
{
    public:
        Move chooseMove(vector<vector<Piece>>) override;
};


#endif

