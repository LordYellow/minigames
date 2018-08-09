
#include "./game.hpp"

int filter(void* argumente, SDL_Event* event){
    return !(event->type == SDL_MOUSEMOTION );
}

int main(){
    SDL_SetEventFilter(filter, NULL);
    
    game spiel;
    
    while(spiel.getStateOfGame()){
        spiel.handleEvents();
        if(spiel.getStateOfGame() == 1) spiel.update();
    }
}

