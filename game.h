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
#include "king.h"
#include "subject.h"


using namespace std;

class Game : public Subject {
    Player* white; // Player is abstract so ptr needed for dynamic type
    Player* black;
    // vector<vector<Piece*>> board;
    std::vector<std::vector<Piece*>> board{8, std::vector<Piece*>(8, nullptr)};

    vector<Piece> deadPieces;

    Player* playerTurn;
    vector<Move> pastMoves;

    public:
        string status;

        // void makeMove();
        char getState(int row, int col) const override;
        // void render();
        // void resign();

        // void resetGame();
        bool gameCreatedViaSetup = false;

        //default constructor 
        Game(): status{"game not started"} {}

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
                white = new Human(WHITE);
            }
            else if (whiteType == "computer1") {
                white = new ComputerOne(WHITE);
            }
            else if (whiteType == "computer2") {
                white = new ComputerTwo(WHITE);
            }
            else if (whiteType == "computer3") {
                white = new ComputerThree(WHITE);
            }
            if (blackType == "human") {
                black = new Human(BLACK);
            }
            else if (blackType == "computer1") {
                black = new ComputerOne(BLACK);
            }
            else if (blackType == "computer2") {
                black = new ComputerTwo(BLACK);
            }
            else if (blackType == "computer3") {
                black = new ComputerThree(BLACK);
            }
        }


        void setup() {
            if(status == "Running") {
                cout << "cannot enter setup mode";
            }

            gameCreatedViaSetup = true;

            std::string command;
            while (std::cin >> command) {
                if(command == "+") {
                    char pieceType;
                    char pieceCol;
                    int pieceRow;
                    cin >> pieceType >> pieceCol >> pieceRow;

                    int rowLoc = 8 - pieceRow;
                    int colLoc = pieceCol - 'a';

                    if(pieceType == 'P') {
                        board[rowLoc][colLoc] = new Pawn(WHITE, 'P');
                    }
                    else if (pieceType == 'K') {
                        board[rowLoc][colLoc] = new King(WHITE, 'K');
                    } else if (pieceType == 'k'){
                        board[rowLoc][colLoc] = new King(BLACK, 'k');
                    }
                    //...

            
                } else if (command == "-") {
                    char pieceCol;
                    int pieceRow;
                    cin >> pieceCol >> pieceRow;

                    int rowLoc = 8 - pieceRow;
                    int colLoc = pieceCol - 'a';

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
                    int numBlackKings = 0; int numWhiteKings = 0;
                    int whiteKingX = 0; int whiteKingY = 0; int blackKingX = 0; int blackKingY = 0;
                    bool pawnWrongSpot = false;

                    for (size_t row = 0; row < board.size(); ++row) {
                        for (size_t col = 0; col < board[row].size(); ++col) {
                            Piece* piece = board[row][col];
                            if(piece != nullptr)  {
                                //pawns not in first or last row
                                if((row == 0 || row == board.size() - 1) && (piece->getPieceType() == 'p' || piece->getPieceType() == 'P')) {
                                    pawnWrongSpot = true;
                                }

                                //update number of White Kings and position
                                if(piece->getPieceType() == 'K') {
                                    numWhiteKings++; whiteKingX = row; whiteKingY = col;
                                }

                                //update number of Black Kings and position
                                if(piece->getPieceType() == 'k') {
                                    numWhiteKings++; blackKingX = row; blackKingY = col;
                                }
                            }
                        }
                    }

                    //make sure the kings arent in check 
                    if (
                        numBlackKings != 1 ||
                        numWhiteKings != 1 ||
                        pawnWrongSpot == true 
                        // || !canAccess(whiteKingX, whiteKingY).isEmspty() || 
                        // !canAccess(blackKingX, blackKingY).isEmpty() ||
                    )  {
                    cout << "Cannot exit setup mode. You have a mistake" << numBlackKings << numWhiteKings << pawnWrongSpot;
                    }
                    else {
                        break;
                    }
                }
            }


            //print the board
            for (size_t row = 0; row < board.size(); ++row) {
                        for (size_t col = 0; col < board[row].size(); ++col) {
                            Piece* piece = board[row][col];
                            if(piece != nullptr)  {
                                cout << piece->getPieceType();
                            } else {
                                cout << " ";
                            }
                            cout << " ";
                        }
                        cout << "\n";
            }

        }
};

#endif
