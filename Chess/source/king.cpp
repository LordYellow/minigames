#include "./../header/king.hpp"
#include "./../header/game.hpp"

#include <iostream>

#define _x this->rect.x/100
#define _y this->rect.y/100

king::king( int x, int y, bool color, game* spiel ): piece(x, y, color, spiel){
        this->id = 0 + color*6;
}

void king::goThroughtFields(){
    for(size_t i = 0; i < this->spiel->pieces.size(); i++){
        if(this->spiel->pieces[i]->getColor() != this->color){
            if(this->spiel->pieces[i]->getID() == 0 || this->spiel->pieces[i]->getID() == 6){
                for(int a = -1; a < 2; a++){
                    for(int b = -1; b < 2; b++){
                        if(a+this->spiel->pieces[i]->getX() >= 0 && a+this->spiel->pieces[i]->getX() <= 7 &&
                        b+this->spiel->pieces[i]->getY() >= 0 && b+this->spiel->pieces[i]->getY() <= 7)
                            this->kingsField[(a+this->spiel->pieces[i]->getX())+(b+this->spiel->pieces[i]->getY())*8] = 1;
                    }
                }
                continue;
            }
            this->spiel->pieces[i]->showMoves();
            for(size_t pia = 0; pia < 64; pia++){
                if(this->spiel->turnsOnField[pia] &&
                !((this->spiel->pieces[i]->getID() == 5 || this->spiel->pieces[i]->getID() == 11) &&
                this->spiel->turnsOnField[pia] == 1)) this->kingsField[pia] = true;
            }
            this->spiel->turnsOnField.fill(0);
        }
    }
}

void king::testField( int x, int y ){
    if(_x+x > 7 || _x+x < 0 || _y+y > 7 || _y+y < 0) return;
    if(this->spiel->field[(_x+x)+(_y+y)*8] != this->color+1 && !this->kingsField[_x+x+(_y+y)*8])
        this->spiel->turnsOnField[(_x+x)+(_y+y)*8] = 1;
}

void king::showMoves(){
    this->kingsField.fill(0);
    this->goThroughtFields();
    this->testField(1,0);
    this->testField(-1,0);
    this->testField(0,1);
    this->testField(0,-1);
    this->testField(1,1);
    this->testField(-1,1);
    this->testField(1,-1);
    this->testField(-1,-1);

    //castle right
    if(this->kingsField[_x+1+_y*8] && this->kingsField[_x+2+_y*8] &&
    this->spiel->field[(_x+1)+(_y)*8] == 0 && this->spiel->field[(_x+2)+(_y)*8] == 0){
        for(size_t i = 0; i < this->spiel->pieces.size(); i++){
            if(this->spiel->pieces[i]->getX() + this->spiel->pieces[i]->getY()*8 == _x+3+_y*8){
                if(this->spiel->pieces[i]->getID() == 4 || this->spiel->pieces[i]->getID() == 10 &&
                this->spiel->pieces[i]->getFirstMove() && this->getFirstMove()){
                    this->spiel->turnsOnField[(_x+2)+(_y)*8] = 1;
                }
                break;
            }
        }
    }

}

bool king::check(){
    this->kingsField.fill(0);
    this->goThroughtFields();
    if(this->kingsField[this->getX()+this->getY()*8]){
        this->spiel->check = this->color+1;
        return true;
    }else return false;
}

bool king::doMove( int x, int y ){
    if(this->spiel->turnsOnField[x+y*8] != 1) return false;
    this->spiel->field[this->rect.x/100+this->rect.y/100*8] = 0;
    this->spiel->turned();
    this->firstMove = false;
    for(size_t i = 0; i < this->spiel->pieces.size(); i++){
        if(this->spiel->pieces[i]->getX() + this->spiel->pieces[i]->getY()*8 == x+y*8){
            delete this->spiel->pieces[i];
            this->spiel->pieces.erase(this->spiel->pieces.begin()+i);
        }
    }

    this->rect.x = x*100;
    this->rect.y = y*100;

    this->spiel->field[this->rect.x/100+this->rect.y/100*8] = color+1;
    this->spiel->turnsOnField.fill(0);

    return true;
}
