#ifndef WINDOW_H
#define WINDOW_H

#include "sprite.h"

typedef struct Window {
    SDL_Window* window;
    SDL_Rect rect;
    Sprite* sprite;
} Window;

Window* Window_Create(const char* title, int x, int y, int width, int height);
int Window_LoadTexture(Window* window, const char* path);
void Window_Destroy(Window* window);
void Window_Render(Window* window, SDL_Renderer* renderer);
SDL_Renderer* Window_GetRenderer(Window* window);



Window* Window_Create(const char* title, int x, int y, int w, int h);
void Window_Destroy(Window* button);
int Window_SetPosition(Window* window, int x, int y);
int Window_SetSize(Window* window, int width, int height);
int Window_SetSprite(Window* button, SDL_Renderer* renderer, const char* path);
int Window_SetIcon(Window* window, const char* filename);

int Window_SyncRectWithSprite(Window* window);

SDL_Renderer* Window_CreateRenderer(Window* window);
SDL_Renderer* Window_GetRenderer(Window* window);

#endif // WINDOW_H