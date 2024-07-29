#ifndef HUMAN_H
#define HUMAN_H

#include <vector>
#include "player.h"
#include <iostream>

using namespace std;

class Human : public Player 
{
    public:
        Human(Colour colour) : Player(colour) {}
        Move chooseMove(const vector<vector<Piece*>>& board) override {

            while(true) {
                char fromCol;
                int fromRow;
                char toCol;
                int toRow;
                
                cin >> fromCol >> fromRow >> toCol >> toRow;
                int fromRowLoc = 8 - fromRow;
                int fromColLoc = fromCol - 'a';
                int toRowLoc = 8 - toRow;
                int toColLoc = toCol - 'a';


                vector<Move> allValidMoves  = findAllMovesICanMake(board);
                // vector<Move> allValidMoves = board.at(fromRowLoc).at(fromColLoc)->getPossibleMoves(board, fromRowLoc, fromColLoc);
                // cout << "allvalidMoves:";
                //     for (Move num : allValidMoves) {
                //         num.getFields();
                //     }
                
                for (size_t i = 0; i < allValidMoves.size(); ++i) {
                    if (
                        fromRowLoc == allValidMoves[i].getFromX() &&
                        fromColLoc == allValidMoves[i].getFromY() &&
                        toRowLoc == allValidMoves[i].getToX() &&
                        toColLoc == allValidMoves[i].getToY()
                    ) {
                        return Move{fromRowLoc, fromColLoc, toRowLoc, toColLoc};
                    }
                }
                cout << "You are not allowed to make that move. Enter a different one.\n";
                string move;
                cin >> move;
            }
        }

};


#endif

