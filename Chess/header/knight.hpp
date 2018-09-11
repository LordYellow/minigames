#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "./piece.hpp"

class knight : public piece {
public:
    knight( int x, int y, bool color, game* spiel );

    void showMoves();
private:
    void testField( int x, int y );
};

#endif
