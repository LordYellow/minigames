#ifndef PIECE_HPP
#define PIECE_HPP

#include <SDL2/SDL.h>
#include <array>

class game;

class piece {
public:
    piece( void ){}
    piece( int x, int y, bool color, game* spiel );

    void draw();
    virtual void showMoves() = 0;
    virtual bool doMove( int x, int y );
    virtual bool check(){return false;}
    virtual bool getFirstMove(){return false;}
    int getX() const;
    int getY() const;
    int getID() const;
    bool getColor() const;
protected:
    game* spiel;
    SDL_Rect rect;
    int id;
    bool color;
};

#endif
