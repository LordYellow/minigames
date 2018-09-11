#include "./../header/knight.hpp"
#include "./../header/game.hpp"

#define _x this->rect.x/100
#define _y this->rect.y/100

knight::knight( int x, int y, bool color, game* spiel ): piece(x, y, color, spiel){
        this->id = 3 + color*6;
}

void knight::testField( int x, int y ){
    if(_x+x > 7 || _x+x < 0 || _y+y > 7 || _y+y < 0) return;
    if(this->spiel->field[(_x+x)+(_y+y)*8] != this->color+1){
        this->spiel->turnsOnField[(_x+x)+(_y+y)*8] = 1;
    }else{
        this->spiel->turnsOnField[(_x+x)+(_y+y)*8] = 2;
    }
}

void knight::showMoves(){
    this->testField(2,1);
    this->testField(2,-1);
    this->testField(-2,1);
    this->testField(-2,-1);
    this->testField(1,2);
    this->testField(1,-2);
    this->testField(-1,2);
    this->testField(-1,-2);
}
