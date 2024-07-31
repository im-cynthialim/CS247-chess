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
    std::vector<std::vector<unique_ptr<Piece>>> board;
    // vector<vector<unique_ptr<Piece>>> board;

    // Player *playerTurn = nullptr;
    std::shared_ptr<Player> playerTurn;
    Colour startColour = WHITE;
    bool pawnPromotionMove( vector<vector<unique_ptr<Piece>>> &board, Move moveToPlay);
    void updateEnPassant( vector<vector<unique_ptr<Piece>>>&board, Move moveToPlay);
    bool executeEnPassant( vector<vector<unique_ptr<Piece>>>&board, Move moveToPlay);

public:
    STATUS status = NOTSTARTED;

    void makeMove()
    {
        Move moveToPlay = playerTurn->chooseMove(board);

        Colour oppCol = WHITE;
        if (playerTurn->getColour() == WHITE)
        {
            oppCol = BLACK;
        }

        //STEP 1: make the move on the board

        //Castle stuffs: move the rook
        if(
            board[moveToPlay.getFromX()][moveToPlay.getFromY()] != nullptr && tolower(board[moveToPlay.getFromX()][moveToPlay.getFromY()]->getPieceType()) == 'k' &&
            abs(moveToPlay.getFromY() - moveToPlay.getToY()) == 2
        ) {
            if(moveToPlay.getFromY() - moveToPlay.getToY() == 2)  { //king moves left (castle far)
                board[moveToPlay.getFromX()][moveToPlay.getFromY() - 4]->hasMoved = true;
                board[moveToPlay.getFromX()][moveToPlay.getFromY() - 1] = move(board[moveToPlay.getFromX()][moveToPlay.getFromY() - 4]);
                // board[moveToPlay.getFromX()][moveToPlay.getFromY() - 1] = board[moveToPlay.getFromX()][moveToPlay.getFromY() - 4]->getCreateNew(board[moveToPlay.getFromX()][moveToPlay.getFromY() - 4]->getColour(), board[moveToPlay.getFromX()][moveToPlay.getFromY() - 4]->getPieceType());
                board[moveToPlay.getFromX()][moveToPlay.getFromY() - 4] = nullptr;
            } else if(moveToPlay.getFromY() - moveToPlay.getToY() == -2) { //king moves right (castle close)
                board[moveToPlay.getFromX()][moveToPlay.getFromY() + 3]->hasMoved = true;
                board[moveToPlay.getFromX()][moveToPlay.getFromY() + 1] = move( board[moveToPlay.getFromX()][moveToPlay.getFromY() + 3]);
                // board[moveToPlay.getFromX()][moveToPlay.getFromY() + 1] = board[moveToPlay.getFromX()][moveToPlay.getFromY() + 3]->getCreateNew(board[moveToPlay.getFromX()][moveToPlay.getFromY() + 3]->getColour(), board[moveToPlay.getFromX()][moveToPlay.getFromY() + 3]->getPieceType());
                board[moveToPlay.getFromX()][moveToPlay.getFromY() + 3] = nullptr;
            }
        }


        // reset en passant
        for (size_t i = 0; i < board.size(); ++i) {
            for (size_t j = 0; j < board.size(); ++j) {
                if (board[i][j] != nullptr && tolower(board[i][j]->getPieceType() == 'p')) {
                    Pawn *pawn = dynamic_cast<Pawn*>(board[i][j].get());
                    pawn->setPassant("left", false);
                    pawn->setPassant("right", false);

                }
            }
        }

        bool wasPromoted = pawnPromotionMove(board, moveToPlay); // check for pawn promotion
        updateEnPassant (board, moveToPlay); // check for en passant potential
        bool execPassant = executeEnPassant (board, moveToPlay); // exec en Passant

        //preform move on the board if its not pawn promotion (even if its castle, need to mov ethe king)
        if(!wasPromoted && !execPassant) {
            board[moveToPlay.getFromX()][moveToPlay.getFromY()]->hasMoved = true;
            if(board[moveToPlay.getToX()][moveToPlay.getToY()] != nullptr) {
                // delete board[moveToPlay.getToX()][moveToPlay.getToY()];
                board[moveToPlay.getToX()][moveToPlay.getToY()] = nullptr;
                
            }

            board[moveToPlay.getToX()][moveToPlay.getToY()] = move(board[moveToPlay.getFromX()][moveToPlay.getFromY()]);
            
            // board[moveToPlay.getToX()][moveToPlay.getToY()] = board[moveToPlay.getFromX()][moveToPlay.getFromY()]->getCreateNew(board[moveToPlay.getFromX()][moveToPlay.getFromY()]->getColour(), board[moveToPlay.getFromX()][moveToPlay.getFromY()]->getPieceType());
            board[moveToPlay.getFromX()][moveToPlay.getFromY()] = nullptr;

        }

        // STEP 2: DID THE MOVE CAUSE A CHECK TO OTHER KING
        bool movePutACheck = false;
        char otherKing = 'k';
        if (oppCol == WHITE)
        {
            otherKing = 'K';
        }

        if (isKingInCheck(otherKing, board))
        {
            movePutACheck = true;
        }

        // STEP 3: Does my opponent have any possible moves?
        vector<Move> oppMoves = playerTurn->findAllMovesOppCanMake(board);

        // STEP 4: Outcome of this move
        if (oppMoves.size() == 0 && movePutACheck == true)
        {
            if (playerTurn->getColour() == WHITE)
            {
                status = WHITEWINS;
                cout << "Checkmate! White wins!\n";
            }
            else
            {
                status = BLACKWINS;
                cout << "Checkmate! Black wins!\n";
            }
        }
        else if (oppMoves.size() == 0 && movePutACheck == false)
        {
            cout << "Stalement\n";
            status = DRAW;
        }
        else if (oppMoves.size() != 0 && movePutACheck == true)
        {
            cout << (oppCol == BLACK ? "Black" : "White") << " is now in check\n";
        }

            // STEP 5: Change the playerTurn
            if(playerTurn->getColour() == WHITE) {
                playerTurn = black;
            } else {
                playerTurn = white;
            }

        notifyObservers();
    }

    char getState(int row, int col) const override;
    void resign()
    {
        // the cur player is resigning
        if (playerTurn->getColour() == BLACK)
        {
            status = WHITEWINS;
            cout << "white wins\n";
        }
        else
        {
            status = BLACKWINS;
            cout << "black wins\n";
        }
    }

    // void resetGame();
    bool gameCreatedViaSetup = false;

    // default constructor
    Game() : status{NOTSTARTED} {

    // vector<unique_ptr<Piece>> emptyRow;

    //     for (int i = 0; i < 8; ++i) {
    //         emptyRow.push_back(nullptr);
    //     }
    

    //     for (int i = 0; i < 8; ++i) {
    //         board.push_back(move(emptyRow));
    //     }

    //     for (int i = 0; i < 8; ++i) {
    //         for (int j = 0; j < 8; ++j) {
    //             cout << "a";
    //         }
    //         cout << "\n";
    //     }
    }

    void setUpGame(const string &whiteType, const string &blackType)
    {
           
        status = RUNNING;
        addPlayersToGame(whiteType, blackType);

        if (!gameCreatedViaSetup)
        {
            vector<unique_ptr<Piece>> boardRow;

            for (int i = 0; i < 8; ++i)
            {
                boardRow.push_back(make_unique<Pawn>(BLACK, 'p'));
            }
            board.push_back(move(boardRow));
            // set up default piece positions
            // black pieces

            boardRow.clear();

            boardRow.push_back(make_unique<Rook>(BLACK, 'r'));
            boardRow.push_back(make_unique<Knight>(BLACK, 'n'));
            boardRow.push_back(make_unique<Bishop>(BLACK, 'b'));
            boardRow.push_back(make_unique<Queen>(BLACK, 'q'));
            boardRow.push_back(make_unique<King>(BLACK, 'k'));
            boardRow.push_back(make_unique<Bishop>(BLACK, 'b'));
            boardRow.push_back(make_unique<Knight>(BLACK, 'n'));
            boardRow.push_back(make_unique<Rook>(BLACK, 'r'));

            board.push_back(move(boardRow));

            // black pawns
          

            


            //4 empty rows
            vector<unique_ptr<Piece>> emptyRow;

            for (int i = 0; i < 8; ++i) {
                emptyRow.push_back(nullptr);
            }
            board.push_back(move(emptyRow));
            for (int i = 0; i < 8; ++i) {
                emptyRow.push_back(nullptr);
            }
            board.push_back(move(emptyRow));
            for (int i = 0; i < 8; ++i) {
                emptyRow.push_back(nullptr);
            }
            board.push_back(move(emptyRow));
            for (int i = 0; i < 8; ++i) {
                emptyRow.push_back(nullptr);
            }
            board.push_back(move(emptyRow));

            // board[0][0] = make_unique<Rook>(BLACK, 'r');
            // board[0][1] = make_unique<Knight>(BLACK, 'n');
            // board[0][2] = make_unique<Bishop>(BLACK, 'b');
            // board[0][3] = make_unique<Queen>(BLACK, 'q');
            // board[0][4] = make_unique<King>(BLACK, 'k');
            // board[0][5] = make_unique<Bishop>(BLACK, 'b');
            // board[0][6] = make_unique<Knight>(BLACK, 'n');
            // board[0][7] = make_unique<Rook>(BLACK, 'r');
            // // black pawns
            // for (int i = 0; i < 8; ++i)
            // {
            //     board[1][i] = make_unique<Pawn>(BLACK, 'p');
            // }

            // white pieces
            
            
            
            // white pawns


            boardRow.clear();
            for (int i = 0; i < 8; ++i)
            {
                boardRow.push_back(make_unique<Pawn>(WHITE, 'p'));
            }
            board.push_back(move(boardRow));

            boardRow.clear();
            boardRow.push_back(make_unique<Rook>(WHITE, 'R'));
            boardRow.push_back(make_unique<Knight>(WHITE, 'N'));
            boardRow.push_back(make_unique<Bishop>(WHITE, 'B'));
            boardRow.push_back(make_unique<Queen>(WHITE, 'Q'));
            boardRow.push_back(make_unique<King>(WHITE, 'K'));
            boardRow.push_back(make_unique<Bishop>(WHITE, 'B'));
            boardRow.push_back(make_unique<Knight>(WHITE, 'N'));
            boardRow.push_back(make_unique<Rook>(WHITE, 'R'));

            board.push_back(move(boardRow));
            // board[7][0] = make_unique<Rook>(WHITE, 'R');
            // board[7][1] = make_unique<Knight>(WHITE, 'N');
            // board[7][2] = make_unique<Bishop>(WHITE, 'B');
            // board[7][3] = make_unique<Queen>(WHITE, 'Q');
            // board[7][4] = make_unique<King>(WHITE, 'K');
            // board[7][5] = make_unique<Bishop>(WHITE, 'B');
            // board[7][6] = make_unique<Knight>(WHITE, 'N');
            // board[7][7] = make_unique<Rook>(WHITE, 'R');


            // for (int i = 0; i < 8; ++i)
            // {

            //     board[6][i] = make_unique<Pawn>(WHITE, 'P');
            // }
        }

        if (startColour == BLACK)
        {
            playerTurn = black;
        }
        else
        {
            playerTurn = white;
        }
    }

    void addPlayersToGame(const string &whiteType, const string &blackType)
    {
        if (whiteType == "human")
        {
            white = make_shared<Human>(WHITE);
            // white = new Human(WHITE);
        }
        else if (whiteType == "computer1")
        {
            white = make_shared<ComputerOne>(WHITE);
            // white = new ComputerOne(WHITE);
        }
        else if (whiteType == "computer2")
        {
            white = make_shared<ComputerTwo>(WHITE);
            // white = new ComputerTwo(WHITE);
        }
        else if (whiteType == "computer3")
        {
            white = make_shared<ComputerThree>(WHITE);
            // white = new ComputerThree(WHITE);
        }
        if (blackType == "human")
        {
            black = make_shared<Human>(BLACK);
            // black = new Human(BLACK);
        }
        else if (blackType == "computer1")
        {
            black = make_shared<ComputerOne>(BLACK);
            // black = new ComputerOne(BLACK);
        }
        else if (blackType == "computer2")
        {
            black = make_shared<ComputerTwo>(BLACK);
            // black = new ComputerTwo(BLACK);
        }
        else if (blackType == "computer3")
        {
            black = make_shared<ComputerThree>(BLACK);
            // black = new ComputerThree(BLACK);
        }
    }

    void setup()
    {
        if (status == RUNNING)
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
                        // delete board[rowLoc][colLoc];
                        board[rowLoc][colLoc] = nullptr;
                    }

                    char toLower = tolower(pieceType); // generalize all inputs to lowercase for faster piece classifying

                    switch (toLower)
                    {
                    // pawn
                    case 'p':
                        board[rowLoc][colLoc] = make_unique<Pawn>(pieceType == 'p' ? BLACK : WHITE, pieceType);
                        // board[rowLoc][colLoc] = new Pawn(pieceType == 'p' ? BLACK : WHITE, pieceType);
                        break;
                    // king
                    case 'k':
                        board[rowLoc][colLoc] = make_unique<King>(pieceType == 'k' ? BLACK : WHITE, pieceType);
                        // board[rowLoc][colLoc] = new King(pieceType == 'k' ? BLACK : WHITE, pieceType);
                        break;
                    // queen
                    case 'q':
                    {
                        board[rowLoc][colLoc] = make_unique<Queen>(pieceType == 'q' ? BLACK : WHITE, pieceType);
                        // board[rowLoc][colLoc] = new Queen(pieceType == 'q' ? BLACK : WHITE, pieceType);
                        break;
                    }
                    // knight
                    case 'n':
                    {
                        board[rowLoc][colLoc] = make_unique<Knight>(pieceType == 'n' ? BLACK : WHITE, pieceType);
                        // board[rowLoc][colLoc] = new Knight(pieceType == 'n' ? BLACK : WHITE, pieceType);
                        break;
                    }
                    // bishop
                    case 'b':
                    {
                        board[rowLoc][colLoc] = make_unique<Bishop>(pieceType == 'b' ? BLACK : WHITE, pieceType);
                        // board[rowLoc][colLoc] = new Bishop(pieceType == 'b' ? BLACK : WHITE, pieceType);
                        break;
                    }
                    // rook
                    case 'r':
                    {
                        board[rowLoc][colLoc] = make_unique<Rook>(pieceType == 'r' ? BLACK : WHITE, pieceType);
                        // board[rowLoc][colLoc] = new Rook(pieceType == 'r' ? BLACK : WHITE, pieceType);
                        break;
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
                    // delete board[rowLoc][colLoc];
                    board[rowLoc][colLoc] = nullptr;
                }
                notifyObservers();
            }
            else if (command == "=")
            {
                string colour;
                cin >> colour;
                if (colour == "black")
                {
                    startColour = BLACK;
                }
                else
                {
                    startColour = WHITE;
                }
            }
            else if (command == "done")
            {
                int numBlackKings = 0;
                int numWhiteKings = 0;
                bool pawnWrongSpot = false;

                for (size_t row = 0; row < board.size(); ++row)
                {
                    for (size_t col = 0; col < board[row].size(); ++col)
                    {
                        unique_ptr<Piece> piece = board[row][col]->getCreateNew(board[row][col]->getColour(), board[row][col]->getPieceType());
                        // Piece *piece = dynamic_cast<Piece>(board[row][col].get());
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
                            }

                            // update number of Black Kings and position
                            if (piece->getPieceType() == 'k')
                            {
                                ++numBlackKings;
                            }
                        }
                    }
                }

                // make sure the kings arent in check
                if (
                    numBlackKings != 1 ||
                    numWhiteKings != 1 ||
                    pawnWrongSpot == true ||
                    isKingInCheck('k', board) ||
                    isKingInCheck('K', board))
                {
                    cout << "Cannot exit setup mode. You have: " << "\n";
                    cout << (numBlackKings != 1 ? (to_string(numBlackKings) + " black Kings") : "") << "\n";
                    cout << (numWhiteKings != 1 ? (to_string(numWhiteKings) + " white Kings") : "") << "\n";
                    cout << (pawnWrongSpot ? " A pawn is in the wrong spot" : "") << "\n";
                    cout << (isKingInCheck('K', board) ? "The white king in check" : "") << "\n";
                    cout << (isKingInCheck('k', board) ? "The black king in check" : "") << "\n";
                }
                else
                {
                    cout << "You successfully completed setup mode" << "\n";
                    break;
                }
            }
        }
    }

    ~Game() {
    // clean up board
    // for (int i = 0; i < board.size(); ++i) {
    //     for (int j = 0; j < board[i].size(); ++j) {
    //         delete board[i][j];
    //         board[i][j] = nullptr;
    //     }
    // }
    // delete white; // delete players
    // delete black;

    // this->detach();

    }
};

#endif
