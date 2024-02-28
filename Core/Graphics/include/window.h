#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

typedef struct Window {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
} Window;

Window* Window_Create(const char* title, int width, int height);

int Window_LoadTexture(Window* window, const char* path);

void Window_Destroy(Window* window);
void Window_Render(Window* window);

SDL_Renderer* Window_GetRenderer(Window* window);

int Window_SetIcon(Window* window, const char* filename);
int Window_SetPosition(Window* window, int x, int y);
int Window_SetSize(Window* window, int width, int height);


#endif // WINDOW_H