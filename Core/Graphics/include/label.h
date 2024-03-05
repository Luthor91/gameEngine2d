#ifndef LABEL_H
#define LABEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "transform.h"

typedef struct Label {
    SDL_Renderer* renderer;
    SDL_Surface* texture;
    Transform* transform;
    SDL_Color* color;
    TTF_Font* font;
    int font_size;
    char* text;
} Label;

/**************************
    Initialisation du label
***************************/

Label* Label_Init(Transform* transform, SDL_Color* color_font, const char* font, char* text, int size_font);

void Label_Renderer(Label* label, SDL_Renderer* renderer);

#endif // LABEL_H
