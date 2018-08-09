#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <map>
#include <math.h>

class game{
public:
    game(void);
    ~game(void);
    
    inline int getStateOfGame();
    void handleEvents();
    void update();
private:
    int stateOfGame = 1;
    bool stateOfBall = 0;
    SDL_Window *win;
    SDL_Renderer *renner;
    SDL_Event event;
    std::map<int, int> keys;
    SDL_Rect line = {400,0,5,15}, player = {100,175,10,50}, enemy = {700,175,10,50}, ball = {150,198, 5, 5}, playerpoints = {5,5,0,5}, enemypoints = {795,5,0,5};
    
    void drawRect(SDL_Rect dst, int r, int g, int b);
    void moveBall();
    
    double ballX = 150, ballY = 198;
    double vX = 2, vY = 0, enemyY = 0;
    int moving = 0;
    
    void moveEnemy();
};

game::game(void){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){std::cout << "error: " << SDL_GetError() << std::endl; return;}
    this->win = SDL_CreateWindow("Titel",100,200,800,400,SDL_WINDOW_SHOWN);
    if(win == nullptr){std::cout << "winerror: " << SDL_GetError() << std::endl; SDL_Quit(); return;}
    this->renner = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renner == nullptr){SDL_DestroyWindow(this->win); std::cout << "renderererror: " << SDL_GetError() << std::endl; SDL_Quit(); return;}
    srand(time(NULL));
}

game::~game(void){
    SDL_DestroyRenderer(this->renner);
    SDL_DestroyWindow(this->win);
    SDL_Quit();
}

inline int game::getStateOfGame(){
    return this->stateOfGame;
}

void game::handleEvents(){
    if(SDL_PollEvent(&this->event)){
        switch(this->event.type){
            case SDL_QUIT: this->stateOfGame = 0; break;
            case SDL_KEYDOWN: this->keys[this->event.key.keysym.sym] = 1; break;
            case SDL_KEYUP: this->keys[this->event.key.keysym.sym] = 0; break;
        }
    }
    
    if(keys[SDLK_w]){if(this->player.y > 0) this->player.y--;}
    if(keys[SDLK_s]){if(this->player.y < 350) this->player.y++;}
    if(keys[SDLK_SPACE]){if(this->stateOfBall == 0) this->stateOfBall = 1;}
}

void game::update(){
    SDL_SetRenderDrawColor(this->renner, 0, 0, 0, 0);
    SDL_RenderClear(this->renner);
    
    for(int i = 0; i < 24; i++){
        this->line.y +=15;
        if(i % 2) this->drawRect(this->line, 100, 100, 100);
    }
    
    this->line.y = 0;
    
    this->moveEnemy();
    
    this->drawRect(this->playerpoints, 100, 100, 100);
    this->drawRect(this->enemypoints, 100, 100, 100);
    this->drawRect(this->player, 150, 150, 150);
    this->drawRect(this->enemy, 150, 150, 150);
    this->drawRect(this->ball, 150, 150, 150);
    
    if(this->stateOfBall) this->moveBall();
    
    SDL_RenderPresent(this->renner);\
    SDL_Delay(1);
}

void game::drawRect(SDL_Rect dst, int r, int g, int b){
    SDL_SetRenderDrawColor(this->renner, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(this->renner, &dst);
}

void game::moveBall(){
    this->ballX += this->vX;
    this->ballY += this->vY;
    
    //wall collision
    if(this->ballY > 400-5){this->vY *= -1;}
    if(this->ballY < 0){this->vY *= -1;}
    if(this->ballX > 800-5){this->playerpoints.w+=5; this->ballX = 150; this->ballY = 200; this->stateOfBall = 0; this->vY = 0; this->vX = 2;}
    if(this->ballX < 0){this->enemypoints.w+=5; this->enemypoints.x-=5; this->ballX = 650; this->ballY = 200; this->vX = -2; this->vY = 0;}
    
    //playercollition
    if(this->ballX < 105){
        int relativY = -this->player.y + this->ball.y + 2.5 - 25;
        if(abs(relativY) <= 25){
            this->vX *= -1;
            this->vY = relativY * 1.9 * M_PI_4/25;
        }
    }
    if(this->ballX > 695){
        int relativY = -this->enemy.y + this->ball.y + 2.5 - 25;
        if(abs(relativY) <= 25){
            this->vX *= -1;
            this->vY = relativY * 1.9 * M_PI_4/25;
        }
    }
    
    this->ball.x = this->ballX;
    this->ball.y = this->ballY;
}

void game::moveEnemy(){
    int relativY = -this->enemy.y + this->ball.y - 2.5 - 25;
    if((!(rand() % 5) && relativY != 0) || this->moving){
        if(!this->moving) moving = 5;
        moving--;
        if(relativY > 0){
            this->enemy.y++;
        }else{
            this->enemy.y--;
        }
    }
}

#endif
