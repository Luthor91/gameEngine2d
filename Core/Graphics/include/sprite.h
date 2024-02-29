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

Sprite* Sprite_Create(SDL_Renderer* renderer, const char* filepath) ;
void Sprite_Destroy(Sprite* sprite);

void Sprite_SetRectangle(Sprite* sprite, SDL_Rect rect);
void Sprite_SetPosition(Sprite* sprite, int x, int y);
void Sprite_SetSize(Sprite* sprite, int width, int height);
void Sprite_SetScale(Sprite* sprite, double scale);
void Sprite_SetRenderer(Sprite* sprite, SDL_Renderer* renderer);

SDL_Rect Sprite_CalcScale(SDL_Rect rect, double scale);

void Sprite_Render(Sprite* sprite);
void Sprite_RenderAll(Sprite** sprites, int numSprites, SDL_Renderer* renderer);

#endif