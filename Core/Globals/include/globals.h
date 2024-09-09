#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>

// Déclaration de la structure qui contient les globales
typedef struct GameGlobals {
    SDL_Renderer* renderer;
    SDL_Window* window;
    int window_width;
    int window_height;
} GameGlobals;

// Déclaration d'une instance globale de cette structure
extern GameGlobals game;

#endif // GLOBALS_H