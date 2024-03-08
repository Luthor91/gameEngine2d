#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "transform.h"

typedef struct Sprite {
    SDL_Texture* texture;
    Transform* transform;
    char* path;
} Sprite;

/**************************
    Initialisation du sprite
***************************/

Sprite* Sprite_Init(SDL_Renderer* renderer, Transform* transform, const char* filepath);

void Sprite_RenderStatic(Sprite* sprite, SDL_Renderer* renderer);
void Sprite_RenderCut(Sprite* sprite, SDL_Renderer* renderer, SDL_Rect* src);
void Sprite_Render(Sprite* sprite, SDL_Renderer* renderer, SDL_RendererFlip flip);

void Sprite_Destroy(Sprite* sprite);

#endif