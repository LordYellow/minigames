#include "./../header/piece.hpp"
#include "./../header/game.hpp"

#include <iostream>

piece::piece( int x, int y, bool color, game* spiel ){
    this->rect.x = x*100;
    this->rect.y = y*100;
    this->rect.h = 100;
    this->rect.w = 100;
    this->color = color;
    this->spiel = spiel;
    this->spiel->field[x+y*8] = color+1;
}

void piece::draw(){
    this->spiel->texture.renderTexture(this->id,this->rect);
}

int piece::getX() const{
    return this->rect.x/100;
}

int piece::getY() const{
    return this->rect.y/100;
}

int piece::getID() const{
    return this->id;
}

bool piece::getColor() const{
    return this->color;
}

bool piece::doMove( int x, int y ){
    if(this->spiel->turnsOnField[x+y*8] != 1) return false;
    this->spiel->field[this->rect.x/100+this->rect.y/100*8] = 0;
    this->spiel->turned();
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
