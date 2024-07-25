#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "player.h"
#include "piece.h"
#include "move.h"


using namespace std;

class Game {
    unique_ptr<Player> white; // Player is abstract so ptr needed for dynamic type
    unique_ptr<Player> black;
    vector<vector<Piece>> board;

    vector<Piece> deadPieces;

    bool isDone;
    string status;

    unique_ptr<Player> playerTurn;
    vector<Move> pastMoves;

    public:
        void makeMove();
        void getState(int, int);
        void render();
        void resign();
        void setup();

        Game(const string& whiteType, const string& blackType) {
            if (whiteType == "human") {
                white = new Human()
            }
        }

        
};

#endif
