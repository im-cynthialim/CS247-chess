#include "game.h"

char Game::getState(int row, int col) const {
    if (this->board.at(row).at(col) != nullptr) { // if there exists a player on the board
        return this->board.at(row).at(col)->getPieceType();
    }
    return '$';
 }