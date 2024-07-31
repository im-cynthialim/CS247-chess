#include <vector>
#include "enums.h"
#include "piece.h"
#include "helperFuncs.h"
#include <memory>

using namespace std;

bool isKingInCheck(char king, const vector<vector<unique_ptr<Piece>>>& board) {
        Colour kingColour = WHITE;
        if (king  == 'k') {
            kingColour = BLACK;
        }

        int kingPosX;
        int kingPosY;
        for (size_t row = 0; row < board.size(); ++row) {
            for (size_t col = 0; col < board[row].size(); ++col) {
                unique_ptr<Piece> piece = board[row][col]->getCreateNew(board[row][col]->getColour(), board[row][col]->getPieceType());
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
                unique_ptr<Piece> piece = board[row][col]->getCreateNew(board[row][col]->getColour(), board[row][col]->getPieceType());
                if(piece != nullptr && piece->getColour() != kingColour) { //other guys piece from the king
                    //find all LINES OF SIGHT moves of other guys pieces on the board
                    vector<Move> possibleMoves = board[row][col]->getLineOfSightMoves(board, row, col);
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

