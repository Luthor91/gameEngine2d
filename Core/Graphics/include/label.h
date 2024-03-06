#ifndef LABEL_H
#define LABEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "transform.h"
#include "font.h"

typedef struct Label {
    SDL_Surface* texture;
    Transform* transform;
    Font* font;
    char* text;
    
} Label;

/**************************
    Initialisation du label
***************************/

Label* Label_Init(Transform* transform, Font* font, char* text);

void Label_RendererStatic(Label* label, SDL_Renderer* renderer);
void Label_RendererTransformable(Label* label, SDL_Renderer* renderer, SDL_RendererFlip flip );

#endif // LABEL_H
