#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <string>
#include <cctype> //to lowercase chars
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
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include "rook.h"
#include "subject.h"

using namespace std;

class Game : public Subject
{
    Player *white; // Player is abstract so ptr needed for dynamic type
    Player *black;
    // vector<vector<Piece*>> board;
    std::vector<std::vector<Piece *>> board{8, std::vector<Piece *>(8, nullptr)};

    vector<Piece> deadPieces;

    Player *playerTurn;
    vector<Move> pastMoves;

public:
    string status;

    // void makeMove();
    char getState(int row, int col) const override;
    // void render();
    // void resign();

    // void resetGame();
    bool gameCreatedViaSetup = false;

    // default constructor
    Game() : status{"game not started"} {}

    void setUpGame(const string &whiteType, const string &blackType)
    {
        status = "Running";
        addPlayersToGame(whiteType, blackType);
        if (!gameCreatedViaSetup)
        {
            // set up default piece positions

            //black pieces
            board[0][0] = new Rook(BLACK, 'r');
            board[0][1] = new Knight(BLACK, 'n');
            board[0][2] = new Bishop(BLACK, 'b');
            board[0][3] = new Queen(BLACK, 'q');
            board[0][4] = new King(BLACK, 'k');
            board[0][5] = new Bishop(BLACK, 'b');
            board[0][6] = new Knight(BLACK, 'n');
            board[0][7] = new Rook(BLACK, 'r');

            // black pawns
            for (int i = 0; i < 8; ++i) {
                board[1][i] = new Pawn(BLACK, 'p');
            }

            // white pieces
            board[7][0] = new Rook(WHITE, 'R');
            board[7][1] = new Knight(WHITE, 'N');
            board[7][2] = new Bishop(WHITE, 'B');
            board[7][3] = new Queen(WHITE, 'Q');
            board[7][4] = new King(WHITE, 'K');
            board[7][5] = new Bishop(WHITE, 'B');
            board[7][6] = new Knight(WHITE, 'N');
            board[7][7] = new Rook(WHITE, 'R');

            // white pawns
            for (int i = 0; i < 8; ++i) {
                board[6][i] = new Pawn(WHITE, 'P');
            }
        }

        if (playerTurn == nullptr)
        {
            playerTurn = white;
        }
    }

    void addPlayersToGame(const string &whiteType, const string &blackType)
    {
        if (whiteType == "human")
        {
            white = new Human(WHITE);
        }
        else if (whiteType == "computer1")
        {
            white = new ComputerOne(WHITE);
        }
        else if (whiteType == "computer2")
        {
            white = new ComputerTwo(WHITE);
        }
        else if (whiteType == "computer3")
        {
            white = new ComputerThree(WHITE);
        }
        if (blackType == "human")
        {
            black = new Human(BLACK);
        }
        else if (blackType == "computer1")
        {
            black = new ComputerOne(BLACK);
        }
        else if (blackType == "computer2")
        {
            black = new ComputerTwo(BLACK);
        }
        else if (blackType == "computer3")
        {
            black = new ComputerThree(BLACK);
        }
    }

    void setup()
    {
        if (status == "Running")
        {
            cout << "Cannot enter setup mode, game in progress";
        }

        gameCreatedViaSetup = true;

        std::string command;
        while (std::cin >> command)
        {
            if (command == "+")
            {
                char pieceType;
                char pieceCol;
                int pieceRow;
                cin >> pieceType >> pieceCol >> pieceRow;

                int rowLoc = 8 - pieceRow;
                int colLoc = pieceCol - 'a';

                if (rowLoc < 0 || rowLoc >= 8 || colLoc < 0 || colLoc >= 8)
                {
                    cout << "Invalid board position" << "\n";
                }
                else
                {

                    if (board[rowLoc][colLoc] != nullptr)
                    {
                        delete board[rowLoc][colLoc];
                        board[rowLoc][colLoc];
                    }

                    char toLower = tolower(pieceType); // generalize all inputs to lowercase for faster piece classifying

                    switch (toLower)
                    {
                    // pawn
                    case 'p':
                        board[rowLoc][colLoc] = new Pawn(pieceType == 'p' ? BLACK : WHITE, pieceType);
                        break;
                    // king
                    case 'k':
                        board[rowLoc][colLoc] = new Pawn(pieceType == 'k' ? BLACK : WHITE, pieceType);
                        break;
                    // queen
                    case 'q':
                    {
                        board[rowLoc][colLoc] = new Pawn(pieceType == 'q' ? BLACK : WHITE, pieceType);
                        break;
                    }
                    // knight
                    case 'n':
                    {
                        board[rowLoc][colLoc] = new Pawn(pieceType == 'n' ? BLACK : WHITE, pieceType);
                        break;
                    }
                    // bishop
                    case 'b':
                    {
                        board[rowLoc][colLoc] = new Pawn(pieceType == 'b' ? BLACK : WHITE, pieceType);
                    }
                    // rook
                    case 'r':
                    {
                        board[rowLoc][colLoc] = new Pawn(pieceType == 'r' ? BLACK : WHITE, pieceType);
                    }
                    default:
                        cerr << "Invalid command" << endl;
                    }
                    notifyObservers();
                }
            }
            else if (command == "-")
            {
                char pieceCol;
                int pieceRow;
                cin >> pieceCol >> pieceRow;

                int rowLoc = 8 - pieceRow;
                int colLoc = pieceCol - 'a';
                
                    if (rowLoc < 0 || rowLoc >= 8 || colLoc < 0 || colLoc >= 8)
                {
                    cout << "Invalid board position" << "\n";
                }

                if (board[rowLoc][colLoc] != nullptr)
                {
                    delete board[rowLoc][colLoc];
                    board[rowLoc][colLoc] = nullptr;
                }
            }
            else if (command == "=")
            {
                string colour;
                if (colour == "black")
                {
                    playerTurn = black; // referring to a player here
                }
                else
                {
                    playerTurn = white;
                }
            }
            else if (command == "done")
            {
                int numBlackKings = 0;
                int numWhiteKings = 0;
                // int whiteKingX = 0; int whiteKingY = 0; int blackKingX = 0; int blackKingY = 0;
                bool pawnWrongSpot = false;

                for (size_t row = 0; row < board.size(); ++row)
                {
                    for (size_t col = 0; col < board[row].size(); ++col)
                    {
                        Piece *piece = board[row][col];
                        if (piece != nullptr)
                        {
                            // pawns not in first or last row
                            if ((row == 0 || row == board.size() - 1) && (piece->getPieceType() == 'p' || piece->getPieceType() == 'P'))
                            {
                                pawnWrongSpot = true;
                            }

                            // update number of White Kings and position
                            if (piece->getPieceType() == 'K')
                            {
                                ++numWhiteKings;
                                // whiteKingX = row;
                                // whiteKingY = col;
                            }

                            // update number of Black Kings and position
                            if (piece->getPieceType() == 'k')
                            {
                                ++numBlackKings;
                                // blackKingX = row;
                                // blackKingY = col;
                            }
                        }
                    }
                }

                // make sure the kings arent in check
                if (
                    numBlackKings != 1 ||
                    numWhiteKings != 1 ||
                    pawnWrongSpot == true
                    // || !canAccess(whiteKingX, whiteKingY).isEmpty() ||
                    // !canAccess(blackKingX, blackKingY).isEmpty() ||
                )
                {
                    cout << "Cannot exit setup mode. You have: " << "\n";
                    cout << (numBlackKings != 1 ? (to_string(numBlackKings) + " black Kings") : "") << "\n";
                    cout << (numWhiteKings != 1 ? (to_string(numWhiteKings) + " white Kings") : "") << "\n";
                    cout << (pawnWrongSpot ? " A pawn is in the wrong spot" : "") << "\n";
                }
                else
                {
                    break;
                }
            }
        }

        // print the board
        // for (size_t row = 0; row < board.size(); ++row)
        // {
        //     for (size_t col = 0; col < board[row].size(); ++col)
        //     {
        //         Piece *piece = board[row][col];
        //         if (piece != nullptr)
        //         {
        //             cout << piece->getPieceType();
        //         }
        //         else
        //         {
        //             cout << " ";
        //         }
        //         cout << " ";
        //     }
        //     cout << "\n";
        // }
    }
};

#endif
