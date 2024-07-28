#ifndef COMPUTERTHREE_H
#define COMPUTERTHREE_H

#include <vector>
#include "computer.h"
#include <iostream>

using namespace std;

class ComputerThree : public Computer 
{
    public:
        ComputerThree(Colour colour) : Computer(colour) {}

        Move chooseMove(const vector<vector<Piece*>>& board) override {
            vector<Move> avoidCaptureMoves = avoidCaptures(board);
            vector<Move> captureMoves = findCaptures(board);
            vector<Move> checkMoves = findChecks(board);


            cout<<"avoidCaptureMoves";
            for (Move num: avoidCaptureMoves) {
                num.getFields();
            }

            

            

            vector<Move> movesToChoose = {};

            //intersect all three
            for (const auto& move1 : avoidCaptureMoves) {
                for (const auto& move2 : captureMoves) {
                    if (move1 == move2) {
                        for (const auto& move3 : checkMoves) {
                            if (move1 == move3) {
                                movesToChoose.push_back(move1);
                                break; // Break out of the innermost loop to avoid duplicate entries
                            }
                        }
                        break; // Break out of the second loop as we've found the match in v2
                    }
                }
            }
            if(movesToChoose.size() > 0) {
                int randomNumber = std::rand() % movesToChoose.size();
                return movesToChoose.at(randomNumber);
            }

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

            //intersect avoid being captured and make a capture move
            for (const auto& move1 : avoidCaptureMoves) {
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

            //avoidBeingCaptured
            if(avoidCaptureMoves.size() > 0) {
                int randomNumber = std::rand() % avoidCaptureMoves.size();
                return avoidCaptureMoves.at(randomNumber);
            }

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

            //check moves
            if(checkMoves.size() > 0) {
                int randomNumber = std::rand() % checkMoves.size();
                return checkMoves.at(randomNumber);
            }

            //capture moves
            if(captureMoves.size() > 0) {
                int randomNumber = std::rand() % captureMoves.size();
                return captureMoves.at(randomNumber);
            }

            vector<Move> allMovesICanMake = findAllMovesICanMake(board);
            int randomNumber = std::rand() % allMovesICanMake.size();
            return allMovesICanMake.at(randomNumber);
        }
};


#endif

