#ifndef PAWN_HPP
#define PAWN_HPP

#include "./piece.hpp"

class pawn : public piece {
public:
    pawn( int x, int y, bool color, game* spiel );

    void showMoves();
    bool doMove( int x, int y );
private:
    bool firstMove = true;
};

#endif
