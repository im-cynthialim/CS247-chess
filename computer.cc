#include <vector>
#include "player.h"
#include "computer.h"

        vector<Move> Computer::findAllMovesOppCanMake(const vector<vector<Piece*>>& board) {
            vector<Move> allMovesOppCanMake = {};
            for (size_t row = 0; row < board.size(); ++row) {
                for (size_t col = 0; col < board[row].size(); ++col) {
                    Piece* piece = board[row][col];
                    if(piece != nullptr && colour != piece->getColour())  {
                        std::vector<Move> additionalMoves = piece->listMoves(board, row, col);
                        allMovesOppCanMake.insert(allMovesOppCanMake.end(), additionalMoves.begin(), additionalMoves.end()); //append
                    }
                }
            }
        }

        vector<Move> Computer::findChecks(const vector<vector<Piece*>>& board) {
            //find all of the moves I can make that will put their king in check 
            char otherKing = 'K';
            if (colour == WHITE) {
                otherKing = 'k';
            }

            int otherKingPosX;
            int otherKingPosY;

            vector<Move> allCheckMoves = {};

            //step 1: find position of their king
            for (size_t row = 0; row < board.size(); ++row) {
                for (size_t col = 0; col < board[row].size(); ++col) {
                    Piece* piece = board[row][col];
                    if(piece != nullptr)  {
                        if(piece->getPieceType() == otherKing) {
                            otherKingPosX = row;
                            otherKingPosY = col;
                        }
                    }
                }
            }

            //step 2: For each of my possible moves, find whether the other king is in check from this move
            //for each of my PIECES, see if it can reach the king
            vector<Move> allMovesICanMake = findAllMovesICanMake(board);
            for (size_t i = 0; i < allMovesICanMake.size(); ++i) {

                //simulate the board if this move was made 
                std::vector<std::vector<Piece*>> boardCopy = board; 
                boardCopy[allMovesICanMake[i].getToX()][allMovesICanMake[i].getToY()] = boardCopy[allMovesICanMake[i].getFromX()][allMovesICanMake[i].getFromY()]; //simulate moving the piece over

                for (size_t row = 0; row < boardCopy.size(); ++row) {
                    for (size_t col = 0; col < boardCopy[row].size(); ++col) {
                        Piece* piece = boardCopy[row][col];
                        if(piece != nullptr && piece->getColour() == this->colour) {
                            //find all possible moves of this piece NOW that the move was simulated
                            vector<Move> possibleMoves = boardCopy[row][col]->listMoves(boardCopy, row, col);
                            for (size_t j = 0; j < possibleMoves.size(); ++j) {
                                if(possibleMoves[j].getToX() == otherKingPosX && possibleMoves[j].getToY() == otherKingPosY) {
                                    allCheckMoves.push_back(allMovesICanMake[i]);
                                    j = possibleMoves.size();
                                    col = boardCopy[row].size();
                                    row = boardCopy.size();
                                    //this move has been added. no need to keep checking if we should add it
                                }
                            }
                        }
                    }
                }
            }

            return allCheckMoves;
        }

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