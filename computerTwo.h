#ifndef COMPUTERTWO_H
#define COMPUTERTWO_H

#include <vector>
#include "computer.h"

using namespace std;

class ComputerTwo : public Computer 
{
    public:
        ComputerTwo(Colour colour) : Computer(colour) {}
        Move chooseMove(vector<vector<Piece*>> board) override {
            vector<Move> captureMoves = findCaptures(board);
            if(captureMoves.size() > 0) {
                int randomNumber = std::rand() % captureMoves.size();
                return captureMoves.at(randomNumber);
            }
            vector<Move> checkMoves = findChecks(board);
            if(checkMoves.size() > 0) {
                int randomNumber = std::rand() % checkMoves.size();
                return checkMoves.at(randomNumber);
            }
            vector<Move> allMovesICanMake = findAllMovesICanMake(board);
            int randomNumber = std::rand() % allMovesICanMake.size();
            return allMovesICanMake.at(randomNumber);
        }
};


#endif

