//
//  game.hpp
//  Chess
//
//  Created by Raphael Straub on 24.08.18.
//  Copyright © 2018 Yellow. All rights reserved.
//

#ifndef game_h
#define game_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include "./textureloader.hpp"
#include <vector>
#include <array>

#include "./piece.hpp"


class game {
public:
    game( void );
    ~game( void );

    bool execute();
    void turned();
    textureloader texture;
    std::array< uint8_t, 64 > field;
    std::array< uint8_t, 64 > turnsOnField;
    std::vector<piece*> pieces;
    bool running = true, winner = true;
    uint8_t check = false, enableEnPassant = 65;
    std::array< piece*, 2 > kingsVector;
private:
    void handleEvents();
    void drawField();

    SDL_Window *win;
    SDL_Renderer *renner;
    SDL_Event event;
    std::unordered_map<int, int> keys;
    bool turn = false, dragAndDrop = false, missedEnPassant = false;
    SDL_Rect fieldRect = {0,0,100,100};
    SDL_Color fieldColor;

    int mouseX, mouseY, mouseID, pieceID;
};

#endif /* game_h */
