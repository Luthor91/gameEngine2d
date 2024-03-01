#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct Sprite {
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Point center;
    double angle;
    double scale;
    char* path;
} Sprite;

#include "../include/sprite.h"

/**************************
    Initialisation du sprite
***************************/
Sprite* Sprite_Create(SDL_Renderer* renderer, const char* filepath);

Sprite* Sprite_Init(SDL_Renderer* renderer, const char* filepath, SDL_Rect rect, SDL_Point pos_center, double scale, double angle);
void Sprite_SetRectangle(Sprite* sprite, SDL_Rect rect);

void Sprite_SetScale(Sprite* sprite, double scale);

void Sprite_SetPosition(Sprite* sprite, int x, int y);

void Sprite_SetCenter(Sprite* sprite, int x, int y);

void Sprite_SetSize(Sprite* sprite, int width, int height);

void Sprite_SetRenderer(Sprite* sprite, SDL_Renderer* renderer);

void Sprite_UpdateCenter(Sprite* sprite);

void Sprite_UpdateRect(Sprite* sprite);

void Sprite_RenderStatic(Sprite* sprite, SDL_Renderer* renderer);
void Sprite_RenderTransformable(Sprite* sprite, SDL_Renderer* renderer, SDL_RendererFlip flip);
void Sprites_RenderStatic(Sprite** sprites, int numSprites, SDL_Renderer* renderer);
void Sprites_RenderTransformable(Sprite** sprites, int numSprites, SDL_Renderer* renderer, SDL_RendererFlip flip );

void Sprite_Destroy(Sprite* sprite);

#endif