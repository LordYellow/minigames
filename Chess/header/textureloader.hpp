//
//  textureloader.hpp
//  Chess
//
//  Created by Raphael Straub on 24.08.18.
//  Copyright © 2018 Yellow. All rights reserved.
//

#ifndef textureloader_h
#define textureloader_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>

class game;

class textureloader{
public:
    textureloader(SDL_Renderer* renner);
    textureloader(void){}

    void renderTexture(int textureID, SDL_Rect dst);

    void drawRectangle(SDL_Rect dst, SDL_Color color, bool fill);
private:
    SDL_Rect rectangle = {0,0,0,0};
    SDL_Renderer* renner;
    SDL_Texture* theTexture;
    game* spiel;
};

#endif /* textureloader_h */
