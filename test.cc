#include <iostream>
#include <vector>
#include <memory>
#include <string>
// #include "game.h"
// #include "player.h"
#include "piece.h"
#include "rook.h"
#include "pawn.h"
#include "enums.h"
#include "move.h"

using namespace std;

int main() {
    std::vector<std::vector<Piece*>> board{8, vector<Piece*>(8, nullptr)};

    Piece* whiteRook = new Rook(WHITE, 'R');
    Piece* whiteRook2 = new Rook(WHITE, 'R');
    Piece* whitePawn = new Pawn(WHITE, 'P');
    Piece* blackPawn = new Pawn(BLACK, 'p');
    Piece* blackPawn2 = new Pawn(BLACK, 'p');

    board.at(0).at(0) = whiteRook; 
    board.at(0).at(1) = whitePawn;
    board.at(1).at(0) = blackPawn;

    board.at(2).at(6) = blackPawn2;
    board.at(7).at(1) = whiteRook2;

    

    // vector<Move> results = whiteRook->listMoves(board, 0, 0); 
    vector<Move> results = blackPawn2->listMoves(board, 2, 6); 


    for (int i = 0; i < results.size(); ++i) {
        cout << "Move " << i << "\n";
        results[i].getFields();
        cout << "\n";
    }


}