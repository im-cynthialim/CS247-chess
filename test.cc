// #include <iostream>
// #include <vector>
// #include <memory>
// #include <string>
// // #include "game.h"
// // #include "player.h"
// #include "piece.h"
// #include "queen.h"
// #include "king.h"
// #include "rook.h"
// // #include "pawn.h"
// // #include "knight.h"
// // #include "bishop.h"
// #include "enums.h"
// #include "move.h"
// // #include "textobserver.h"

// using namespace std;

// int main() {
//     std::vector<std::vector<Piece*>> board{8, vector<Piece*>(8, nullptr)};

    

//     // Piece* whiteRook = new Rook(WHITE, 'R');
//     // Piece* whiteRook2 = new Rook(WHITE, 'R');
//     // Piece* whitePawn = new Pawn(WHITE, 'P');
//     // Piece* blackPawn = new Pawn(BLACK, 'p');
//     // Piece* blackPawn2 = new Pawn(BLACK, 'p');
//     // Piece* blackKnight = new Knight(BLACK, 'n');
//     // Piece* blackBishop = new Bishop(BLACK, 'b');
//     // Piece* blackQueen = new Queen(BLACK, 'q');

//     Piece* blackRook = new Rook(BLACK, 'r');
//     Piece* blackKing = new King(BLACK, 'k');
//     Piece* whiteQueen = new Queen(WHITE, 'Q');


//     // board.at(0).at(0) = whiteRook; 
//     // board.at(0).at(1) = whitePawn;
//     // board.at(1).at(0) = blackPawn;

//     // board.at(2).at(6) = blackPawn2;
//     // board.at(7).at(1) = whiteRook2;
//     // board.at(3).at(4) = blackKnight;
//     // board.at(3).at(3) = blackBishop;

//     board[3][6] = blackKing;
//     board[2][3] = blackRook;
//     board[0][6] = whiteQueen;

//     // board.at(2).at(4) = whitePawn;


// // const std::vector<std::vector<Piece*>>& constBoard = board;
    

//     // vector<Move> results = whiteRook->listMoves(board, 0, 0); 
//     // vector<Move> results = blackPawn2->listMoves(board, 2, 6); 

//     // vector<Move> results = blackKnight->listMoves(board, 0, 0); 
//     // vector<Move> results = blackBishop->listMoves(board, 3, 3); 
//     // vector<Move> results = blackQueen->listMoves(board, 3, 3); 


//     // vector<Move> results = blackRook->getPossibleMoves(board,2,3);
//     vector<Move> results = whiteQueen->getLineOfSightMoves(board, 0, 6); 



//     // line of Sight implemented - all valid moves
//     // returns moves

//     // possiblesMoves calls line of sight
//     // for each of the moves returned from line of sight, call line of sight on enemy's pieces 
//     // from enemy's line of sight, see if my king is in it

//     // if yes, then my initial move is invalid
//     // if no, then final list of possible moves has initial move

//     // possibleMoves - is my king within my line of sight + am i not in check?
//     // yes, then limit moves if line of sight of enemy has me in it + up to that enemy is empty squares
//     // if my king is not in my line of sight + we're not in check we can move anywhere
    
    
    
//     // Game *testGame = new Game;


//     // new TextObserver(testGame);
    
//     // testGame->notifyObservers();

    

    



//     for (int i = 0; i < results.size(); ++i) {
//         cout << "Move " << i << "\n";
//         results[i].getFields();
//         cout << "\n";
//     }


// }