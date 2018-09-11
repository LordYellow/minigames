#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "./piece.hpp"

class queen : public piece {
public:
    queen( int x, int y, bool color, game* spiel );

    void showMoves();
private:
    void goThroughtFieldsDiagonal( bool toX, bool toY );
    void goThroughtFieldsNormal( bool xoy, bool sign );
};

#endif
