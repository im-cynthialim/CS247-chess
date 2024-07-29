// helperFuncs.h
#ifndef HELPERFUNCS_H
#define HELPERFUNCS_H
#include <vector>
#include "enums.h"
#include "piece.h"

// function declarations
bool isKingInCheck(char king, const vector<vector<Piece*>>& board);

#endif // HELPERFUNCS_H
