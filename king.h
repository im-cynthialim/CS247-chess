#ifndef KING_H
#define KING_H

#include <vector>
#include "piece.h"
#include <memory>
using namespace std;

class King: public Piece {
    vector<Move> lineOfSight(const  vector<vector<unique_ptr<Piece>>> &, int, int) override;
    vector<Move> possibleMoves(const  vector<vector<unique_ptr<Piece>>> &, int, int) override;

    
    

    public:
        King(Colour c, char pieceType);
        unique_ptr<Piece> createNew(Colour colour, char pieceType) override {
        return make_unique<King>(colour, pieceType);
    }
        virtual ~King();
};

#endif
