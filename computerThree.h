#ifndef COMPUTERTHREE_H
#define COMPUTERTHREE_H

#include <vector>
#include "computer.h"

using namespace std;

class ComputerThree : public Computer 
{
    public:
        ComputerThree(Colour colour) : Computer(colour) {}
        Move chooseMove(vector<vector<Piece*>> board) override {
            vector<Move> avoidCaptureMoves = avoidCaptures(board);
            if(avoidCaptureMoves.size() > 0) {
                int randomNumber = std::rand() % avoidCaptureMoves.size();
                return avoidCaptureMoves.at(randomNumber);
            }
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

