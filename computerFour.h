#ifndef COMPUTERFOUR_H
#define COMPUTERFOUR_H

#include <vector>
#include "computer.h"
#include <iostream>

using namespace std;

class ComputerFour : public Computer 
{
    public:
        ComputerFour(Colour colour) : Computer(colour) {}

        Move chooseMove(const vector<vector<Piece*>>& board) override {
            vector<Move> avoidCaptureMoves = avoidCaptures(board);
            vector<Move> captureMoves = findMostValuableCaptures(board);
            vector<Move> checkMoves = findChecks(board);    
    

            //intersect all three
            for (const auto& move1 : avoidCaptureMoves) {
                for (const auto& move2 : captureMoves) {
                    if (move1 == move2) {
                        for (const auto& move3 : checkMoves) {
                            if (move1 == move3) {
                                return move1; //this is going to be the best move since it's closest to the front of captureMoves
                            }
                        }
                        break; // Break out of the second loop as we've found the match in v2
                    }
                }
            }

            //intersect avoid being captured and make a capture move
            for (const auto& move1 : avoidCaptureMoves) {
                for (const auto& move2 : captureMoves) {
                    if (move1 == move2) {
                        return move1; //this is going to be the best move since it's closest to the front of captureMoves
                    }
                }
            }

            vector<Move> movesToChoose = {};
            //intersect avoid being captured and put king in check
            for (const auto& move1 : avoidCaptureMoves) {
                for (const auto& move2 : checkMoves) {
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

            //intersect put king in check and make a capture
            for (const auto& move1 : checkMoves) {
                for (const auto& move2 : captureMoves) {
                    if (move1 == move2) {
                        return move1;
                    }
                }
            }

            //capture moves
            if(captureMoves.size() > 0) {
                return captureMoves.at(0); 
            }

            //avoidBeingCaptured
            if(avoidCaptureMoves.size() > 0) {
                int randomNumber = std::rand() % avoidCaptureMoves.size();
                return avoidCaptureMoves.at(randomNumber); //this is going to be the best move since it's closest to the front of captureMoves
            }

            //check moves
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

