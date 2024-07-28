#ifndef HUMAN_H
#define HUMAN_H

#include <vector>
#include "player.h"

using namespace std;

class Human : public Player 
{
    public:
        Human(Colour colour) : Player(colour) {}
        Move chooseMove(const vector<vector<Piece*>>& board) override {
            char fromCol;
            char fromRow;
            char toCol;
            char toRow;

            while(true) {
                cin >> fromCol >> fromRow >> toCol >> toRow;
                int fromRowLoc = 8 - fromRow;
                int fromColLoc = fromCol - 'a';
                int toRowLoc = 8 - toRow;
                int toColLoc = toCol - 'a';

                Move myMove = Move{fromRowLoc, fromColLoc, toRowLoc, toColLoc};

                vector<Move> allValidMoves = findAllMovesICanMake(board);
                bool isValidMove = false;
                for (size_t i = 0; i < allValidMoves.size(); ++i) {
                    if (
                        myMove.getFromX() == allValidMoves[i].getFromX() &&
                        myMove.getFromY() == allValidMoves[i].getFromY() &&
                        myMove.getToX() == allValidMoves[i].getToX() &&
                        myMove.getToY() == allValidMoves[i].getToY()
                    ) {
                        i = allValidMoves.size();
                        isValidMove = true;
                    }
                }

                if(isValidMove) {
                    return myMove;
                } else {
                    cout << "You are not allowed to make that move. Enter a different one.";
                }
            }
        }
};


#endif

