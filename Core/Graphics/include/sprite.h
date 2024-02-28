#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct Sprite {
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;
} Sprite;

Sprite* Sprite_Create(SDL_Renderer* renderer, const char* filepath) ;
void Sprite_Destroy(Sprite* sprite);

void Sprite_SetRectangle(Sprite* sprite, SDL_Rect rect);
void Sprite_SetPosition(Sprite* sprite, int x, int y);
void Sprite_SetSize(Sprite* sprite, int width, int height);

void Sprite_Render(Sprite* sprite);

#endif