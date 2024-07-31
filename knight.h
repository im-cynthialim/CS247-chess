#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>
#include "piece.h"
#include <memory>

using namespace std;

class Knight : public Piece {
    vector<Move> lineOfSight(const  vector<vector<unique_ptr<Piece>>> &, int, int) override;

    public:
        Knight(Colour c, char pieceType); 
        virtual ~Knight();
        unique_ptr<Piece> createNew(Colour colour, char pieceType) override {
        return make_unique<Knight>(colour, pieceType);
    }
};

#endif
