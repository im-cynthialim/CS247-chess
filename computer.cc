#include <vector>
#include "player.h"
#include "computer.h"
#include <algorithm>

         vector<Move> Computer::findCaptures(const vector<vector<Piece*>>& board) {
            vector<Move> allfindCaptureMoves = {};
            vector<Move> allMovesICanMake = findAllMovesICanMake(board);
            if(colour == WHITE) {
                for (size_t i = 0; i < allMovesICanMake.size(); ++i) {
                    if(board[allMovesICanMake[i].getToX()][allMovesICanMake[i].getToY()] != nullptr && board[allMovesICanMake[i].getToX()][allMovesICanMake[i].getToY()]->getColour() == BLACK) {
                        allfindCaptureMoves.push_back(allMovesICanMake[i]);
                    }
                }
            }

            else if(colour == BLACK) {
                for (size_t i = 0; i < allMovesICanMake.size(); ++i) {
                    if(board[allMovesICanMake[i].getToX()][allMovesICanMake[i].getToY()] != nullptr && board[allMovesICanMake[i].getToX()][allMovesICanMake[i].getToY()]->getColour() == WHITE) {
                        allfindCaptureMoves.push_back(allMovesICanMake[i]);
                    }
                }
            }

            return allfindCaptureMoves;
        }

        vector<Move> Computer::avoidCaptures(const vector<vector<Piece*>>& board) {
            vector<Move> allMovesICanMake = findAllMovesICanMake(board);
            vector<Move> avoidCaptureMoves = {};

            for (size_t i = 0; i < allMovesICanMake.size(); ++i) {
                std::vector<std::vector<Piece*>> boardCopy = board;
                boardCopy[allMovesICanMake[i].getToX()][allMovesICanMake[i].getToY()] = boardCopy[allMovesICanMake[i].getFromX()][allMovesICanMake[i].getFromY()]; //simulate moving the piece over
                boardCopy[allMovesICanMake[i].getFromX()][allMovesICanMake[i].getFromY()] = nullptr;
                vector<Move> allMovesOppPlayer = findAllMovesOppCanMake(boardCopy);

                bool didIfRun = false;
                for(size_t j = 0; j < allMovesOppPlayer.size(); ++j) {
                    if(allMovesICanMake[i].getToX() == allMovesOppPlayer[j].getToX() && allMovesICanMake[i].getToY() == allMovesOppPlayer[j].getToY()) {
                        didIfRun = true;
                        j = allMovesOppPlayer.size(); //end inner for loop 
                    }
                }
                if(!didIfRun) {
                    avoidCaptureMoves.push_back(allMovesICanMake[i]);
                }
            }

            return avoidCaptureMoves;
        }


         vector<Move> Computer::findMostValuableCaptures(const vector<vector<Piece*>>& board) {
               // Find all the capture moves
                vector<Move> allCaptureMoves = this->findCaptures(board);

                // Define the order of priority from most valuable to least valuable
                string priority = "qrnbp"; // Queen, Rook, Bishop, Knight, Pawn

                // Sort the capture moves by the value of the captured piece
                sort(allCaptureMoves.begin(), allCaptureMoves.end(),
                    [&board, &priority](Move move1, Move move2) {
                        Piece* capturedPiece1 = board[move1.getToX()][move1.getToY()];
                        Piece* capturedPiece2 = board[move2.getToX()][move2.getToY()];

                        // Get the index in the priority string, lower index means higher priority
                        int priority1 = priority.find(tolower(capturedPiece1->getPieceType()));
                        int priority2 = priority.find(tolower(capturedPiece2->getPieceType()));

                        return priority1 < priority2;
                    });

                return allCaptureMoves;
         }
        
