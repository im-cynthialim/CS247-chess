#ifndef QUEEN_H
#define QUEEN_H

#include <vector>
#include "piece.h"
#include <memory>
using namespace std;

class Queen : public Piece {
    vector<Move> lineOfSight(const  vector<vector<unique_ptr<Piece>>> &, int, int) override;
    
    public:
        Queen(Colour c, char pieceType);
        unique_ptr<Piece> createNew(Colour colour, char pieceType) override {
        return make_unique<Queen>(colour, pieceType);
    }
        virtual ~Queen();
};


#endif
