//
//  textureloader.cpp
//  Chess
//
//  Created by Raphael Straub on 24.08.18.
//  Copyright © 2018 Yellow. All rights reserved.
//

#include "./../header/textureloader.hpp"

textureloader::textureloader(SDL_Renderer* renner){
    this->renner = renner;
    this->theTexture = SDL_CreateTextureFromSurface(this->renner, IMG_Load("./resources/pieces.png"));
    this->rectangle.h = 213;
    this->rectangle.w = 213;
}

void textureloader::renderTexture(int textureID, SDL_Rect dst){
    int w, h;
    SDL_QueryTexture(this->theTexture, NULL, NULL, &w, &h);
    this->rectangle.x = (textureID % 6)*213;
    this->rectangle.y = (textureID/6)*213;
    SDL_RenderCopy(this->renner, this->theTexture, &this->rectangle, &dst);
}

void textureloader::drawRectangle(SDL_Rect dst, SDL_Color color, bool fill){
    SDL_SetRenderDrawColor(this->renner, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    if(fill){SDL_RenderFillRect(this->renner, &dst);}else{SDL_RenderDrawRect(this->renner, &dst);}
}
