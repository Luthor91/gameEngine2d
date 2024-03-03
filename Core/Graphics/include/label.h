#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct Label {
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    SDL_Color* color;
    SDL_Rect rect;
    SDL_Point center;
    //SDL_Texture texture;
    double angle;
    double scale;
} Label;



/**************************
    Initialisation du label
***************************/
Label* Label_Init(SDL_Renderer* renderer, SDL_Rect rect, SDL_Point center, SDL_Color color_font, char* font, char* text, int size_font, double scale, double angle);

#endif