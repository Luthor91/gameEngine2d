#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL_ttf.h>
#include "../../Graphics/include/color.h"

typedef struct Font {
    TTF_Font* ttf;
    Color* color;
    char* path;
    int size;
} Font;

int Font_Start();
Font* Font_Init(Color* color, char* path, int size);

#endif // FONT_H