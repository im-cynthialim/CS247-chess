#ifndef ROOK_H
#define ROOK_H

#include <vector>
#include "piece.h"
#include <memory>

using namespace std;

class Rook : public Piece {
    vector<Move> lineOfSight(const  vector<vector<unique_ptr<Piece>>> &, int, int) override;


    public: 
        Rook(Colour c, char piecetype);
            unique_ptr<Piece> createNew(Colour colour, char pieceType) override {
        return make_unique<Rook>(colour, pieceType);
    }
        virtual ~Rook();
};

#endif
