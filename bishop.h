#ifndef BISHOP_H
#define BISHOP_H

#include <vector>
#include "piece.h"
#include <memory>

using namespace std;

class Bishop : public Piece {
    vector<Move> lineOfSight(const  vector<vector<unique_ptr<Piece>>> &, int, int) override;
  
    public:
        Bishop(Colour c, char pieceType);
        virtual ~Bishop();
          unique_ptr<Piece> createNew(Colour colour, char pieceType) override {
        return make_unique<Bishop>(colour, pieceType);
    }
};


#endif
