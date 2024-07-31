#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <utility>
#include <string>
#include <cctype> //to lowercase chars
#include <vector>
#include "player.h"
#include "human.h"
#include "computerOne.h"
#include "computerTwo.h"
#include "computerThree.h"
#include "computerFour.h"
#include "piece.h"
#include "move.h"
#include "enums.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include "rook.h"
#include "subject.h"
#include "helperFuncs.h"

using namespace std;

class Game : public Subject
{
    std::shared_ptr<Player> white;
    
    // Player *white = nullptr; // Player is abstract so ptr needed for dynamic type
    std::shared_ptr<Player> black;
    // Player *black = nullptr;
    std::vector<std::vector<Piece *>> board{8, std::vector<Piece *>(8, nullptr)};
    // Player *playerTurn = nullptr;
    std::shared_ptr<Player> playerTurn;
    Colour startColour = WHITE;
    bool pawnPromotionMove(vector<vector<Piece*>> &board, Move moveToPlay);
    void updateEnPassant(vector<vector<Piece*>>&board, Move moveToPlay);
    bool executeEnPassant(vector<vector<Piece*>>&board, Move moveToPlay);

public:
    STATUS status = NOTSTARTED;
    
    void makeMove();
    char getState(int row, int col) const override;
    void resign();


    bool gameCreatedViaSetup = false;

    // default constructor
    // Game() : status{NOTSTARTED} {}

    void setUpGame(const string&, const string &);

    void addPlayersToGame(const string&, const string&);
    void setup();

~Game();
};

#endif
