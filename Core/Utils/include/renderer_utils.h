#ifndef RENDERER_UTILS_H
#define RENDERER_UTILS_H

#include <SDL2/SDL.h>
#include <stdio.h>

extern SDL_Renderer* g_renderer;

// Fonction pour créer un SDL_Renderer
SDL_Renderer* createRenderer(SDL_Window* window);

#endif // RENDERER_UTILS_H