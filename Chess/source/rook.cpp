#include "./../header/rook.hpp"
#include "./../header/game.hpp"
#include "./../header/stuff.hpp"

#define _x this->rect.x/100
#define _y this->rect.y/100

rook::rook( int x, int y, bool color, game* spiel ): piece(x, y, color, spiel){
        this->id = 4 + color*6;
}

void rook::goThroughtFields( bool xoy, bool sign ){
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

void rook::showMoves(){
    this->goThroughtFields(0,0);
    this->goThroughtFields(0,1);
    this->goThroughtFields(1,0);
    this->goThroughtFields(1,1);
}

bool rook::doMove( int x, int y ){
    if(this->spiel->turnsOnField[x+y*8] != 1) return false;
    this->firstMove = false;
    this->spiel->turned();
    this->spiel->field[this->rect.x/100+this->rect.y/100*8] = 0;

    for(size_t i = 0; i < this->spiel->pieces.size(); i++){
        if(this->spiel->pieces[i]->getX() + this->spiel->pieces[i]->getY()*8 == x+y*8){
            delete this->spiel->pieces[i];
            this->spiel->pieces.erase(this->spiel->pieces.begin()+i);
        }
    }

    this->rect.x = x*100;
    this->rect.y = y*100;

    this->spiel->field[this->rect.x/100+this->rect.y/100*8] = color+1;

    return true;
}
