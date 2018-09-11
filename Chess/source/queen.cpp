#include "./../header/queen.hpp"
#include "./../header/game.hpp"
#include "./../header/stuff.hpp"

#define _x this->rect.x/100
#define _y this->rect.y/100

extern int boolToNegative( bool );

queen::queen( int x, int y, bool color, game* spiel ): piece(x, y, color, spiel){
        this->id = 1 + color*6;
}

void queen::goThroughtFieldsDiagonal( bool toX, bool toY ){
    int x = _x, y = _y;
    do{
        y += boolToNegative(toY);
        x += boolToNegative(toX);
        if(x < 0 || x > 7 || y < 0 || y > 7) return;
        if(this->spiel->field[x+(y)*8] != this->color+1){
            this->spiel->turnsOnField[x+(y)*8] = 1;
            if(this->spiel->field[x+(y)*8] != 0) return;
        }else {
            this->spiel->turnsOnField[x+(y)*8] = 2;
            return;
        }
    }while(true);
}

void queen::goThroughtFieldsNormal( bool xoy, bool sign ){
    int x = _x, y = _y;
    do{
        if(!xoy) y += boolToNegative(sign);
        do{
            if(xoy) x += boolToNegative(sign);
            if(x < 0 || x > 7 || y < 0 || y > 7) return;
            if(this->spiel->field[x+(y)*8] != this->color+1){
                this->spiel->turnsOnField[x+(y)*8] = 1;
                if(this->spiel->field[x+(y)*8] != 0) return;
            }else {
                this->spiel->turnsOnField[x+(y)*8] = 2;
                return;
            }
        }while((x > 0 && x < 7) && xoy);
    }while((y > 0 && y < 7) && !xoy);
}

void queen::showMoves(){
    this->goThroughtFieldsDiagonal(0,0);
    this->goThroughtFieldsDiagonal(0,1);
    this->goThroughtFieldsDiagonal(1,0);
    this->goThroughtFieldsDiagonal(1,1);
    this->goThroughtFieldsNormal(0,0);
    this->goThroughtFieldsNormal(0,1);
    this->goThroughtFieldsNormal(1,0);
    this->goThroughtFieldsNormal(1,1);
}
