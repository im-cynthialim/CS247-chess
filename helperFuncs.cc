#include <vector>
#include "enums.h"
#include "piece.h"
#include "helperFuncs.h"

bool isKingInCheck(char king, const vector<vector<Piece*>>& board) {
        Colour kingColour = WHITE;
        if (king  == 'k') {
            kingColour = BLACK;
        }

        int kingPosX;
        int kingPosY;
        for (size_t row = 0; row < board.size(); ++row) {
            for (size_t col = 0; col < board[row].size(); ++col) {
                Piece* piece = board[row][col];
                if(piece != nullptr)  {
                    if(piece->getPieceType() == king) {
                        kingPosX = row;
                        kingPosY = col;
                    }
                }
            }
        }

        for (size_t row = 0; row < board.size(); ++row) {
            for (size_t col = 0; col < board[row].size(); ++col) {
                Piece* piece = board[row][col];
                if(piece != nullptr && piece->getColour() != kingColour) { //other guys piece from the king
                    //find all LINES OF SIGHT moves of other guys pieces on the board
                    vector<Move> possibleMoves = board[row][col]->getLineOfSightMoves(board, row, col);

                    // if(piece->getPieceType() == 'q') {
                    //     for(Move num: possibleMoves) {
                    //         num.getFields();
                    //     }
                    // }


                    for (size_t j = 0; j < possibleMoves.size(); ++j) {
                        if(possibleMoves[j].getToX() == kingPosX && possibleMoves[j].getToY() == kingPosY) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
    