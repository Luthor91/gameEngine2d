#ifndef WINDOW_H
#define WINDOW_H

#include "sprite.h"
#include "aspect.h"

typedef struct Window {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Aspect* aspect;
    Sprite* sprite;
} Window;

Window* Window_Create(const char* title, Aspect* aspect);
Window* Window_Init(const char* title, Aspect* aspect, const char* sprite_path);
int Window_SetIcon(Window* window, const char* filename);
SDL_Renderer* Window_CreateRenderer(Window* window);
SDL_Renderer* Window_GetRenderer(Window* window);
int Window_SetSprite(Window* window, const SDL_Renderer* renderer, const char* path);

#endif // WINDOW_H