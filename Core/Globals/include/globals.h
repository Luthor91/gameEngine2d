#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../../Globals/include/constants.h"

// Déclaration de la structure qui contient les globales
typedef struct GameGlobals {
    SDL_Renderer* renderer;
    SDL_Window* window;
    int window_width;
    int window_height;
} GameGlobals;

// Déclaration d'une instance globale de cette structure
extern GameGlobals game;

// Tableau pour stocker les états des entités
extern bool *entityStates;
extern bool *hasSprite;
extern bool *hasPosition;
extern bool *hasVelocity;
extern bool *hasInput;
extern bool *hasTransform;
extern bool *hasAnimation;
extern bool *hasHitbox;
extern bool *hasSize;
extern bool *hasTags;
extern bool *hasDatas;

#endif // GLOBALS_H