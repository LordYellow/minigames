#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "./piece.hpp"

class bishop : public piece {
public:
    bishop( int x, int y, bool color, game* spiel );

    void showMoves();
private:
    void goThroughtFields( bool toX, bool toY );
};

#endif
