#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "player.h"
#include "human.h"
#include "computerOne.h"
#include "computerTwo.h"
#include "computerThree.h"
#include "piece.h"
#include "move.h"
#include "enums.h"


using namespace std;

class Game {
    Player* white; // Player is abstract so ptr needed for dynamic type
    Player* black;
    // vector<vector<Piece*>> board;
    std::vector<std::vector<Piece*>> board{8, std::vector<Piece*>(8, nullptr)};

    vector<Piece> deadPieces;

    Player* playerTurn;
    vector<Move> pastMoves;

    public:
        string status;

        void makeMove();
        void getState(int, int);
        void render();
        void resign();

        void resetGame();
        bool gameCreatedViaSetup = false;

        //default constructor 
        Game(): status{"game not started"}, gameCreatedViaSetup{"false"} {}

        void setUpGame(const string& whiteType, const string& blackType) {
            status = "Running";
            addPlayersToGame(whiteType, blackType);
            if(!gameCreatedViaSetup) {
                //set up the board 
            }

            if(playerTurn == nullptr) {
                playerTurn = white;
            }
        }


        void addPlayersToGame(const string& whiteType, const string& blackType) {
            if (whiteType == "human") {
                // white = unique_ptr<Human>(new Human(WHITE, true));
                white = new Human(WHITE, true);
            }
            else if (whiteType == "computer1") {
                // white = unique_ptr<ComputerOne>(new ComputerOne(WHITE, true));
                white = new ComputerOne(WHITE, true);
            }
            else if (whiteType == "computer2") {
                // white = unique_ptr<ComputerTwo>(new ComputerTwo(WHITE, true));
                white = new ComputerTwo(WHITE, true);
            }
            else if (whiteType == "computer3") {
                // white = unique_ptr<ComputerThree>(new ComputerThree(WHITE, true));
                white = new ComputerThree(WHITE, true);
            }
            if (blackType == "human") {
                // black = unique_ptr<Human>(new Human(BLACK, true));
                black = new Human(BLACK, true);
            }
            else if (blackType == "computer1") {
                // black = unique_ptr<ComputerOne>(new ComputerOne(BLACK, true));
                black = new ComputerOne(BLACK, true);
            }
            else if (blackType == "computer2") {
                // black = unique_ptr<ComputerTwo>(new ComputerTwo(BLACK, true));
                black = new ComputerTwo(BLACK, true);
            }
            else if (blackType == "computer3") {
                // black = unique_ptr<ComputerThree>(new ComputerThree(BLACK, true));
                black = new ComputerThree(BLACK, true);
            }
        }


        void setup() {
            if(status == "Running") {
                cout << "cannot enter setup mode";
            }

            gameCreatedViaSetup = true;
            while (true) {
                // string setupCommand;
                // std::getline(std::cin, setupCommand);

                // if (setupCommand ... ) {

            }
        }

};

#endif
