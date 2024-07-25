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
#include "pawn.h"


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
                white = new Human(WHITE, true);
            }
            else if (whiteType == "computer1") {
                white = new ComputerOne(WHITE, true);
            }
            else if (whiteType == "computer2") {
                white = new ComputerTwo(WHITE, true);
            }
            else if (whiteType == "computer3") {
                white = new ComputerThree(WHITE, true);
            }
            if (blackType == "human") {
                black = new Human(BLACK, true);
            }
            else if (blackType == "computer1") {
                black = new ComputerOne(BLACK, true);
            }
            else if (blackType == "computer2") {
                black = new ComputerTwo(BLACK, true);
            }
            else if (blackType == "computer3") {
                black = new ComputerThree(BLACK, true);
            }
        }


        void setup() {
            if(status == "Running") {
                cout << "cannot enter setup mode";
            }

            std::string command;
            while (std::cin >> command) {
                if(command == "+") {
                    char pieceType;
                    string pieceLocation;
                    cin >> pieceType >> pieceLocation;

                    int rowLoc = 8 - pieceLocation[0];
                    int colLoc = pieceLocation[1]  - 'a';

                    if(pieceType == 'p') {
                        board[rowLoc][colLoc] = new Pawn(WHITE, 'p');
                    }

                    


                } else if (command == "-") {
                    string pieceLocation;
                    cin >> pieceLocation;

                    int rowLoc = 8 - pieceLocation[0];
                    int colLoc = pieceLocation[1]  - 'a';

                    if(board[rowLoc][colLoc] != nullptr) {
                        delete board[rowLoc][colLoc];
                    }
                } else if (command == "=") {
                    string colour;
                    if(colour == "black") {
                        playerTurn = black;
                    } else {
                        playerTurn = white;
                    }

                } else if (command == "done") {


                }
            }

            gameCreatedViaSetup = true;
            while (true) {

            }
        }
};

#endif
