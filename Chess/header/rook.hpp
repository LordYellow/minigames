#ifndef ROOK_HPP
#define ROOK_HPP

#include "./piece.hpp"

class rook : public piece {
public:
    rook( int x, int y, bool color, game* spiel );

    void showMoves();
    bool doMove( int x, int y );
    bool getFirstMove(){return this->firstMove;}
private:
    void goThroughtFields( bool xoy, bool sign );
    bool firstMove = true;
};

#endif
