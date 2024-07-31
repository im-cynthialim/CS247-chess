// helperFuncs.h
#ifndef HELPERFUNCS_H
#define HELPERFUNCS_H
#include <vector>
#include "enums.h"
#include <memory>
// #include "piece.h"
class Piece;


// function declarations
bool isKingInCheck(char king, const vector<vector<unique_ptr<Piece>>>& board);

#endif // HELPERFUNCS_H
