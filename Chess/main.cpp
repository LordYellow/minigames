//
//  main.cpp
//  Chess
//
//  Created by Raphael Straub on 24.08.18.
//  Copyright © 2018 Yellow. All rights reserved.
//

#include <iostream>
#include "./header/game.hpp"

int filter(void* argumente, SDL_Event* event){
    return (event->type != SDL_MULTIGESTURE &&
        event->type != SDL_DOLLARGESTURE && event->type != SDL_MULTIGESTURE &&
        event->type != SDL_FINGERMOTION && event->type != SDL_FINGERDOWN &&
        event->type != SDL_FINGERUP);
}

int main(int argc, const char * argv[]) {
    SDL_SetEventFilter(filter, NULL);

    game spiel;

    if(spiel.execute()){
        std::cout << "Player 1 Wins" << std::endl;
    }else{
        std::cout << "Player 2 Wins" << std::endl;
    }

    return 0;
}
