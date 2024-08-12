#ifndef WINDOW_UTILS_H
#define WINDOW_UTILS_H

#include <SDL2/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Fonction pour créer une SDL_Window
SDL_Window* createWindow(const char* title);

#endif // WINDOW_UTILS_H