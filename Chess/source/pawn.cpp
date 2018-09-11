#include "./../header/pawn.hpp"
#include "./../header/stuff.hpp"
#include "./../header/game.hpp"
#include "./../header/queen.hpp"

#include <iostream>

#define _x this->rect.x/100
#define _y this->rect.y/100

pawn::pawn( int x, int y, bool color, game* spiel ): piece(x, y, color, spiel){
        this->id = 5 + color*6;
}

void pawn::showMoves(){
    for (int i = 1; i < (this->firstMove+2); i++){
        if(this->spiel->field[this->rect.x/100+(this->rect.y/100+i*boolToNegative(this->color))*8] == 0)
            this->spiel->turnsOnField[this->rect.x/100+(this->rect.y/100+i*boolToNegative(this->color))*8] = 1;
    }
    if(this->spiel->field[this->rect.x/100-1+(this->rect.y/100+boolToNegative(this->color))*8] == !this->color+1){
        this->spiel->turnsOnField[this->rect.x/100-1+(this->rect.y/100+boolToNegative(this->color))*8] = 1;}else{
            if(this->rect.x/100-1+(this->rect.y/100+boolToNegative(this->color))*8 == this->spiel->enableEnPassant){
                this->spiel->turnsOnField[this->rect.x/100-1+(this->rect.y/100+boolToNegative(this->color))*8] = 1;
            }else
            this->spiel->turnsOnField[this->rect.x/100-1+(this->rect.y/100+boolToNegative(this->color))*8] = 2;
        }
    if(this->spiel->field[this->rect.x/100+1+(this->rect.y/100+boolToNegative(this->color))*8] == !this->color+1){
        this->spiel->turnsOnField[this->rect.x/100+1+(this->rect.y/100+boolToNegative(this->color))*8] = 1;}else{
            if(this->rect.x/100+1+(this->rect.y/100+boolToNegative(this->color))*8 == this->spiel->enableEnPassant){
                this->spiel->turnsOnField[this->rect.x/100+1+(this->rect.y/100+boolToNegative(this->color))*8] = 1;
            }else
            this->spiel->turnsOnField[this->rect.x/100+1+(this->rect.y/100+boolToNegative(this->color))*8] = 2;
        }
}

bool pawn::doMove( int x, int y ){
    if(this->spiel->turnsOnField[x+y*8] != 1) return false;
    if(y+2 == _y) this->spiel->enableEnPassant = x+(y+1)*8; else if(y-2 == _y) this->spiel->enableEnPassant= x+(y-1)*8;
    this->firstMove = false;
    this->spiel->turned();
    if(x+y*8 == this->spiel->enableEnPassant){
        int a;
        (y+1 == _y)?(a = 1):(a = -1);
        for(size_t i = 0; i < this->spiel->pieces.size(); i++){
            if(this->spiel->pieces[i]->getX() + this->spiel->pieces[i]->getY()*8 == x+(y+a)*8){
                delete this->spiel->pieces[i];
                this->spiel->pieces.erase(this->spiel->pieces.begin()+i);
            }
        }
    }
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
    this->spiel->turnsOnField.fill(0);

    if(y == 7 || y == 0){
        this->spiel->pieces.push_back(new queen(x,y,this->color,this->spiel));
        for(size_t i = 0; i < this->spiel->pieces.size(); i++){
            if(this->spiel->pieces[i] == this){
                this->spiel->pieces.erase(this->spiel->pieces.begin()+i);
                break;
            }
        }
        delete this;
    }
    return true;
}
