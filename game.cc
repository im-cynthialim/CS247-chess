#include "game.h"
#include <memory>

using namespace std;

char Game::getState(int row, int col) const {
    if (this->board.at(row).at(col) != nullptr) { // if there exists a player on the board
        return this->board.at(row).at(col)->getPieceType();
    }
    return '$';
}

bool Game::pawnPromotionMove(vector<vector<Piece*>> &board, Move moveToPlay) {
    string validPieces = "qrnbQRNB";
    char promoteTo = ' ';
    bool pawnPromotion = false;

    char pieceType = board[moveToPlay.getFromX()][moveToPlay.getFromY()]->getPieceType();
    bool isWhitePawn = (pieceType == 'P');
    bool isBlackPawn = (pieceType == 'p');
    bool isPromotionRow = (moveToPlay.getToX() == (isWhitePawn ? 0 : 7));

    if ((isWhitePawn || isBlackPawn) && isPromotionRow) {
        if (dynamic_pointer_cast<Human>(playerTurn)) {
            cin >> promoteTo;
            
            while (validPieces.find(promoteTo) == string::npos) {
                cout << "Invalid piece for promotion, choose again" << "\n";
                cin >> promoteTo;
            }
            pawnPromotion = true;
        } else {
            // Choose promotion piece if computer
            promoteTo = isWhitePawn ? 'Q' : 'q';
            pawnPromotion = true;
        }
    }

    if (pawnPromotion) {
        // Determine the color based on the pawn's original color
        Colour color = (isWhitePawn ? WHITE : BLACK);
        
        // Create the new piece based on the promotion choice
        Piece* newPiece = nullptr;
        switch (tolower(promoteTo)) {
            case 'q': newPiece = new Queen(color, promoteTo); break;
            case 'n': newPiece = new Knight(color, promoteTo); break;
            case 'b': newPiece = new Bishop(color, promoteTo); break;
            case 'r': newPiece = new Rook(color, promoteTo); break;
            default: newPiece = new Queen(color, promoteTo); break;
        }
        
        // Debugging output
        cout << "Promoting pawn at (" << moveToPlay.getFromX() << ", " << moveToPlay.getFromY() << ") to "
             << promoteTo << " at (" << moveToPlay.getToX() << ", " << moveToPlay.getToY() << ")" << endl;
        
        // Move the piece and delete the old pawn
        delete board[moveToPlay.getFromX()][moveToPlay.getFromY()];
        board[moveToPlay.getFromX()][moveToPlay.getFromY()] = nullptr;
        board[moveToPlay.getToX()][moveToPlay.getToY()] = newPiece;
        return true;
    }
    return false;
}



void Game::updateEnPassant(vector<vector<Piece*>> &board, Move moveToPlay) {
    if(board[moveToPlay.getFromX()][moveToPlay.getFromY()] == nullptr) {
        // return false;
    }

      if (board[moveToPlay.getFromX()][moveToPlay.getFromY()] != nullptr && board[moveToPlay.getFromX()][moveToPlay.getFromY()]->getPieceType() == 'p' && moveToPlay.getFromX() == 1 && moveToPlay.getToX() == 3)
            {
                // if our move is a two-square move of a black pawn
            if (moveToPlay.getToY() + 1 < 8 && board[moveToPlay.getToX()][moveToPlay.getToY() + 1] != nullptr && board[moveToPlay.getToX()][moveToPlay.getToY() + 1]->getPieceType() == 'P')
            {
                static_cast<Pawn *>(board[moveToPlay.getToX()][moveToPlay.getToY() + 1])->setPassant("left", true);
                // return true;

            }

            if (moveToPlay.getToY() - 1 >= 0 && board[moveToPlay.getToX()][moveToPlay.getToY() - 1] != nullptr && board[moveToPlay.getToX()][moveToPlay.getToY() - 1]->getPieceType() == 'P')
            {
                static_cast<Pawn *>(board[moveToPlay.getToX()][moveToPlay.getToY() - 1])->setPassant("right", true);
                // return true;
            }
            
        }
        else if (board[moveToPlay.getFromX()][moveToPlay.getFromY()] != nullptr && board[moveToPlay.getFromX()][moveToPlay.getFromY()]->getPieceType() == 'P' && moveToPlay.getFromX() == 6 && moveToPlay.getToX() == 4)
        {
            // if our move is a two-square move of a white pawn
            if (moveToPlay.getToY() + 1 < 8 && board[moveToPlay.getToX()][moveToPlay.getToY() + 1] != nullptr && board[moveToPlay.getToX()][moveToPlay.getToY() + 1]->getPieceType() == 'p')
            {
                static_cast<Pawn *>(board[moveToPlay.getToX()][moveToPlay.getToY() + 1])->setPassant("right", true);
                // return true;
            }
            if (moveToPlay.getToY() - 1 >= 0 && board[moveToPlay.getToX()][moveToPlay.getToY() - 1] != nullptr && board[moveToPlay.getToX()][moveToPlay.getToY() - 1]->getPieceType() == 'p')
            {
                static_cast<Pawn *>(board[moveToPlay.getToX()][moveToPlay.getToY() - 1])->setPassant("left", true);
            }
            // return true;
        }
        // return false;
}

bool Game::executeEnPassant(vector<vector<Piece*>> &board, Move moveToPlay) {
     if ((moveToPlay.getFromX() == 3 || moveToPlay.getFromX() == 4) && tolower(board[moveToPlay.getFromX()][moveToPlay.getFromY()]->getPieceType()) == 'p' && moveToPlay.getToY() != moveToPlay.getFromY() && board[moveToPlay.getToX()][moveToPlay.getToY()] == nullptr) {
            // making an en passant move
            if (moveToPlay.getFromX() > moveToPlay.getToX()) {
                delete board[moveToPlay.getToX() + 1][moveToPlay.getToY()]; // delete captured pawn
                board[moveToPlay.getToX() + 1][moveToPlay.getToY()] = nullptr;
            }
            else {
                delete board[moveToPlay.getToX() - 1][moveToPlay.getToY()]; // delete captured pawn
                board[moveToPlay.getToX() - 1][moveToPlay.getToY()] = nullptr;
            }
            
            board[moveToPlay.getToX()][moveToPlay.getToY()] = board[moveToPlay.getFromX()][moveToPlay.getFromY()];
            board[moveToPlay.getFromX()][moveToPlay.getFromY()] = nullptr;
        return true;
        }
        return false;
}
