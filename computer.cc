#include <vector>
#include "player.h"
#include "computer.h"
#include <memory>

         vector<Move> Computer::findCaptures(const  vector<vector<unique_ptr<Piece>>>& board) {
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

        vector<Move> Computer::avoidCaptures(const  vector<vector<unique_ptr<Piece>>>& board) {
            vector<Move> allMovesICanMake = findAllMovesICanMake(board);
            vector<Move> avoidCaptureMoves = {};

           for (size_t i = 0; i < allMovesICanMake.size(); ++i) {
                //simulate the board if this move was made 
                  vector<vector<unique_ptr<Piece>>> boardCopy;
                for (size_t r = 0; r < board.size(); ++r)
                {
                    for (size_t c = 0; c < board[r].size(); ++c)
                    {
                        if (boardCopy[r][c] != nullptr) {
                            boardCopy[r][c] = board[r][c]->getCreateNew(board[r][c]->getColour(), board[r][c]->getPieceType());
                        }
                        else {
                            boardCopy[r][c] = nullptr;
                        }
                        // boardCopy[r][c] != nullptr ? board[r][c]->getCreateNew(board[r][c]->getColour(), board[r][c]->getPieceType()) : nullptr;
                    }
                }
                boardCopy[allMovesICanMake[i].getToX()][allMovesICanMake[i].getToY()] = boardCopy[allMovesICanMake[i].getFromX()][allMovesICanMake[i].getFromY()]->getCreateNew(boardCopy[allMovesICanMake[i].getFromX()][allMovesICanMake[i].getFromY()]->getColour(), boardCopy[allMovesICanMake[i].getFromX()][allMovesICanMake[i].getFromY()]->getPieceType()); //simulate moving the piece over
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
        
