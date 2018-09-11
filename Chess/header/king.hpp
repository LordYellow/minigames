#ifndef KING_HPP
#define KING_HPP

#include <array>

#include "./piece.hpp"

class king : public piece {
public:
    king( int x, int y, bool color, game* spiel );

    void showMoves();
    bool check();
    bool doMove( int x, int y );
private:
    void goThroughtFields();
    void testField( int x, int y );
    std::array< bool, 64 > kingsField;
    bool firstMove = true;
};

#endif
