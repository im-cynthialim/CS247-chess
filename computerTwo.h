#ifndef COMPUTERTWO_H
#define COMPUTERTWO_H

#include <vector>
#include "computer.h"

using namespace std;

class ComputerTwo : public Computer 
{
    public:
        ComputerTwo(Colour colour) : Computer(colour) {}
        Move chooseMove(const vector<vector<Piece*>>& board) override {
            vector<Move> captureMoves = findCaptures(board);
            vector<Move> checkMoves = findChecks(board);

            vector<Move> movesToChoose = {};
            //intersect put king in check and make a capture
            for (const auto& move1 : checkMoves) {
                for (const auto& move2 : captureMoves) {
                    if (move1 == move2) {
                        movesToChoose.push_back(move1);
                        break; // Break out of the innermost loop to avoid duplicate entries
                    }
                }
            }
            if(movesToChoose.size() > 0) {
                int randomNumber = std::rand() % movesToChoose.size();
                return movesToChoose.at(randomNumber);
            }
            if(captureMoves.size() > 0) {
                int randomNumber = std::rand() % captureMoves.size();
                return captureMoves.at(randomNumber);
            }
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

