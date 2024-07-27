#include <vector>
#include "player.h"
#include "computer.h"

         vector<Move> Computer::findCaptures(vector<vector<Piece*>>& board) {
            vector<Move> allfindCaptureMoves = {};
            vector<Move> allMovesICanMake = findAllMovesICanMake(board);
            if(colour == WHITE) {
                for (size_t i = 0; i < allMovesICanMake.size(); ++i) {
                    if(board[allMovesICanMake[i].getToX()][allMovesICanMake[i].getToY()] != nullptr && board[allMovesICanMake[i].getToX()][allMovesICanMake[i].getToY()]->getColour() == BLACK) {
                        allfindCaptureMoves.push_back(allMovesICanMake[i]);
                    }
                }
            }
        }

        vector<Move> Computer::avoidCaptures(vector<vector<Piece*>>& board) {
            vector<Move> allMovesICanMake = findAllMovesICanMake(board);
            vector<Move> allMovesOppPlayer = findAllMovesOppCanMake(board);

            for (size_t i = 0; i < allMovesICanMake.size(); ++i) {
                //if a move that I can make is inside a move that the opponenet can make, BAD, dont add it 
                bool didIfRun = false;
                for(size_t j = 0; j < allMovesOppPlayer.size(); ++j) {
                    if(allMovesICanMake[i].getToX() == allMovesOppPlayer[j].getToX() && allMovesICanMake[i].getToY() == allMovesOppPlayer[j].getToY()) {
                        didIfRun = true;
                        j = allMovesOppPlayer.size(); //end inner for loop 
                    }
                }
                if(!didIfRun) {
                    allMovesICanMake.push_back(allMovesICanMake[i]);
                }
            }
        }