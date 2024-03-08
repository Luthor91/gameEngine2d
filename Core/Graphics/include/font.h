#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL_ttf.h>

typedef struct Font {
    TTF_Font* ttf;
    SDL_Color* color;
    char* path;
    int size;
  
} Font;

int Font_Start();
Font* Font_Init(SDL_Color* color, char* path, int size);

#endif // FONT_H