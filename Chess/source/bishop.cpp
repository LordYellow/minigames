#include "./../header/bishop.hpp"
#include "./../header/game.hpp"
#include "./../header/stuff.hpp"

#define _x this->rect.x/100
#define _y this->rect.y/100

bishop::bishop( int x, int y, bool color, game* spiel ): piece(x, y, color, spiel){
        this->id = 2 + color*6;
}

void bishop::goThroughtFields( bool toX, bool toY ){
    int x = _x, y = _y;
    do{
        y += boolToNegative(toY);
        x += boolToNegative(toX);
        if(x < 0 || x > 7 || y < 0 || y > 7) return;
        if(this->spiel->field[x+(y)*8] != this->color+1){
            this->spiel->turnsOnField[x+(y)*8] = 1;
            if(this->spiel->field[x+(y)*8] != 0) return;
        }else{
            this->spiel->turnsOnField[x+(y)*8] = 2;
            return;
        }
    }while(true);
}

void bishop::showMoves(){
    this->goThroughtFields(0,0);
    this->goThroughtFields(0,1);
    this->goThroughtFields(1,0);
    this->goThroughtFields(1,1);
}
