#include "game.h"

char Game::getState(int row, int col) const {
    if (this->board.at(row).at(col) != nullptr) { // if there exists a player on the board
        return this->board.at(row).at(col)->getPieceType();
    }
    return '$';
}

bool Game::pawnPromotionMove(vector<vector<Piece*>> &board, Move moveToPlay) {
       string validPieces = "qrnb";
       char promoteTo = 'p';
       bool pawnPromotion = false;

    if (board[moveToPlay.getFromX()][moveToPlay.getFromY()]->getPieceType() == 'p' && moveToPlay.getToX() == 7)
            if (dynamic_cast<Human *>(playerTurn))
            {
                cin >> promoteTo;

                while (validPieces.find(promoteTo) == string::npos)
                {
                    cout << "Invalid piece for promotion, choose again" << "\n";
                    cin >> promoteTo;
                }
                pawnPromotion = true;
            }
            else
            { // choose promotion piece if computer
                promoteTo = 'q';
            }

        else if (board[moveToPlay.getFromX()][moveToPlay.getFromY()]->getPieceType() == 'P' && moveToPlay.getToX() == 0)
        { // check for white pawn promotion
            string validPieces = "QRNB";
            if (dynamic_cast<Human *>(playerTurn))
            {
                cin >> promoteTo;

                while (validPieces.find(promoteTo) == string::npos)
                {
                    cout << "Invalid piece for promotion, choose again" << "\n";
                    cin >> promoteTo;
                }
                pawnPromotion = true;
            }
        }
        else
        { // choose promotion piece if computer
            promoteTo = 'Q';
            pawnPromotion = true;
        }

        if (pawnPromotion) {
          switch (tolower(promoteTo))
            {

            // queen
            case 'q':
            {
                board[moveToPlay.getToX()][moveToPlay.getToY()] = new Queen(tolower(promoteTo) == 'q' ? BLACK : WHITE, promoteTo);
                break;
            }
            // knight
            case 'n':
            {
                board[moveToPlay.getToX()][moveToPlay.getToY()] = new Knight(tolower(promoteTo) == 'n' ? BLACK : WHITE, promoteTo);
                break;
            }
            // bishop
            case 'b':
            {
                board[moveToPlay.getToX()][moveToPlay.getToY()] = new Bishop(tolower(promoteTo) == 'b' ? BLACK : WHITE, promoteTo);
                break;
            }
            // rook
            case 'r':
            {
                board[moveToPlay.getToX()][moveToPlay.getToY()] = new Rook(tolower(promoteTo) == 'r' ? BLACK : WHITE, promoteTo);
                break;
            }
            default:
                board[moveToPlay.getToX()][moveToPlay.getToY()] = new Queen(tolower(promoteTo) == 'q' ? BLACK : WHITE, promoteTo);
                break;
            }

            // replace pawn with piece chosen
            delete board[moveToPlay.getFromX()][moveToPlay.getFromY()];
            board[moveToPlay.getFromX()][moveToPlay.getFromY()] = nullptr;
            return true;
        }
        return false;
}

bool Game::updateEnPassant(vector<vector<Piece*>> &board, Move moveToPlay) {
    if(board[moveToPlay.getFromX()][moveToPlay.getFromY()] == nullptr) {
        return false;
    }

      if (board[moveToPlay.getFromX()][moveToPlay.getFromY()]->getPieceType() == 'p' && moveToPlay.getFromX() == 1 && moveToPlay.getToX() == 3)
            {
                // if our move is a two-square move of a black pawn
            if (moveToPlay.getToY() + 1 < 8 && board[moveToPlay.getToX()][moveToPlay.getToY() + 1] != nullptr && board[moveToPlay.getToX()][moveToPlay.getToY() + 1]->getPieceType() == 'P')
            {
                static_cast<Pawn *>(board[moveToPlay.getToX()][moveToPlay.getToY() + 1])->setPassant("left", true);

            }

            if (moveToPlay.getToY() - 1 >= 0 && board[moveToPlay.getToX()][moveToPlay.getToY() - 1] != nullptr && board[moveToPlay.getToX()][moveToPlay.getToY() - 1]->getPieceType() == 'P')
            {
                static_cast<Pawn *>(board[moveToPlay.getToX()][moveToPlay.getToY() - 1])->setPassant("right", true);
            }
            return true;
        }
        else if (board[moveToPlay.getFromX()][moveToPlay.getFromY()]->getPieceType() == 'P' && moveToPlay.getFromX() == 6 && moveToPlay.getToX() == 4)
        {
            // if our move is a two-square move of a white pawn
            if (moveToPlay.getToY() + 1 < 8 && board[moveToPlay.getToX()][moveToPlay.getToY() + 1] != nullptr && board[moveToPlay.getToX()][moveToPlay.getToY() + 1]->getPieceType() == 'p')
            {
                static_cast<Pawn *>(board[moveToPlay.getToX()][moveToPlay.getToY() + 1])->setPassant("right", true);
            }
            if (moveToPlay.getToY() - 1 >= 0 && board[moveToPlay.getToX()][moveToPlay.getToY() - 1] != nullptr && board[moveToPlay.getToX()][moveToPlay.getToY() - 1]->getPieceType() == 'p')
            {
                static_cast<Pawn *>(board[moveToPlay.getToX()][moveToPlay.getToY() - 1])->setPassant("left", true);
            }
            return true;
        }
        return false;
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