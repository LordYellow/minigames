//
//  game.cpp
//  Chess
//
//  Created by Raphael Straub on 24.08.18.
//  Copyright © 2018 Yellow. All rights reserved.
//

#include <iostream>

#include "./../header/game.hpp"
#include "./../header/pawn.hpp"
#include "./../header/rook.hpp"
#include "./../header/knight.hpp"
#include "./../header/bishop.hpp"
#include "./../header/queen.hpp"
#include "./../header/king.hpp"



game::game( void ){
    this->field.fill(0);
    this->turnsOnField.fill(0);
    //SDL init stuff
    if(SDL_Init(SDL_INIT_VIDEO) != 0){std::cout << "error: " << SDL_GetError() << std::endl; return;}
    this->win = SDL_CreateWindow("Titel",100,200,800,800,SDL_WINDOW_SHOWN);
    if(win == nullptr){std::cout << "winerror: " << SDL_GetError() << std::endl; SDL_Quit(); return;}
    this->renner = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renner == nullptr){SDL_DestroyWindow(this->win); std::cout << "renderererror: " << SDL_GetError() << std::endl; SDL_Quit(); return;}
    this->texture = textureloader(this->renner);

    for(size_t i = 0; i < 8; i++){
        this->pieces.push_back(new pawn(i,1,1,this));
        this->pieces.push_back(new pawn(i,6,0,this));
    }
    this->pieces.push_back(new rook(0,0,1,this));
    this->pieces.push_back(new rook(7,0,1,this));
    this->pieces.push_back(new rook(0,7,0,this));
    this->pieces.push_back(new rook(7,7,0,this));

    this->pieces.push_back(new knight(1,0,1,this));
    this->pieces.push_back(new knight(6,0,1,this));
    this->pieces.push_back(new knight(1,7,0,this));
    this->pieces.push_back(new knight(6,7,0,this));

    this->pieces.push_back(new bishop(2,0,1,this));
    this->pieces.push_back(new bishop(5,0,1,this));
    this->pieces.push_back(new bishop(2,7,0,this));
    this->pieces.push_back(new bishop(5,7,0,this));

    this->pieces.push_back(new queen(3,0,1,this));
    this->pieces.push_back(new queen(3,7,0,this));

    piece *king2 = new king(4,0,1,this);
    piece *king1 = new king(4,7,0,this);

    this->pieces.push_back(king1);
    this->pieces.push_back(king2);

    this->kingsVector[0] = king1;
    this->kingsVector[1] = king2;
}

game::~game(){
    for(size_t i = 0; i < this->pieces.size(); i++){
        delete this->pieces[i];
    }
    SDL_DestroyRenderer(this->renner);
    SDL_DestroyWindow(this->win);
    SDL_Quit();
}

bool game::execute(){
    while(this->running){
        SDL_SetRenderDrawColor(this->renner, 0, 0, 0, 0);
        SDL_RenderClear(this->renner);

        this->handleEvents();
        this->drawField();
        for(size_t i = 0; i < this->pieces.size(); i++){
            this->pieces[i]->draw();
        }
        if(this->dragAndDrop){
            this->fieldRect.y = this->mouseY -50;
            this->fieldRect.x = this->mouseX -50;
            this->texture.renderTexture(this->mouseID,this->fieldRect);
        }

        SDL_RenderPresent(this->renner);\
        SDL_Delay(1);
    }
    return this->winner;
}


void game::handleEvents(){
    if(SDL_PollEvent(&this->event)){
        switch(this->event.type){
            case SDL_QUIT: this->running = false; break;
            case SDL_KEYDOWN: this->keys[this->event.key.keysym.sym] = 1; break;
            case SDL_KEYUP: this->keys[this->event.key.keysym.sym] = 0; break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&this->mouseX, &this->mouseY);
                if(!this->field[this->mouseX/100 + this->mouseY/100 * 8]) break;
                this->pieceID = this->mouseX/100 + this->mouseY/100 * 8;
                if(this->enableEnPassant != 65)
                    this->missedEnPassant = true;
                for(size_t i = 0; i < this->pieces.size(); i++){
                    if(this->pieces[i]->getX() + this->pieces[i]->getY()*8 == this->pieceID){
                        if(this->pieces[i]->getColor() != this->turn) return;
                        this->mouseID = this->pieces[i]->getID();
                        this->pieces[i]->showMoves();
                        break;
                    }
                }
                this->dragAndDrop = true;
                break;
            case SDL_MOUSEBUTTONUP:
                SDL_GetMouseState(&this->mouseX, &this->mouseY);
                this->dragAndDrop = false;
                for(size_t i = 0; i < this->pieces.size(); i++){
                    if(this->pieces[i]->getX() + this->pieces[i]->getY()*8 == this->pieceID){
                        if(this->pieces[i]->doMove(this->mouseX/100, this->mouseY/100) && this->missedEnPassant){
                            this->missedEnPassant = false;
                            this->enableEnPassant = 65;
                        }
                    }
                }
                this->turnsOnField.fill(0);
                this->check = false;
                this->kingsVector[0]->check();
                this->kingsVector[1]->check();
                break;
            case SDL_MOUSEMOTION:
                SDL_GetMouseState(&this->mouseX, &this->mouseY);
            default: break;
        }
    }
}

void game::drawField(){
    for(int y = 0; y < 8; y++){
        for(int x = 0; x < 8; x++){
            ((y%2)^(x%2))?(this->fieldColor = {50,50,50,0}):(this->fieldColor = {200,200,200,0});
            this->fieldRect.y = y*100;
            this->fieldRect.x = x*100;

            this->texture.drawRectangle(this->fieldRect, this->fieldColor, true);
            if(this->turnsOnField[x+y*8] == 1){
                this->fieldColor = {255,200,0,0};
                this->texture.drawRectangle(this->fieldRect, this->fieldColor, false);
            }
        }
    }
    if(this->check){
        this->fieldRect.y = this->kingsVector[this->check-1]->getY()*100;
        this->fieldRect.x = this->kingsVector[this->check-1]->getX()*100;
        this->fieldColor = {255,0,0,0};
        this->texture.drawRectangle(this->fieldRect, this->fieldColor, false);
    }
}

void game::turned(){
    this->turn = !turn;
}
