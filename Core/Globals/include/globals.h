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
extern bool entityStates[MAX_ENTITIES];
extern bool hasSprite[MAX_ENTITIES];
extern bool hasPosition[MAX_ENTITIES];
extern bool hasVelocity[MAX_ENTITIES];
extern bool hasInput[MAX_ENTITIES];
extern bool hasTransform[MAX_ENTITIES];
extern bool hasAnimation[MAX_ENTITIES];
extern bool hasHitbox[MAX_ENTITIES];
extern bool hasSize[MAX_ENTITIES];
extern bool hasTags[MAX_ENTITIES];
extern bool hasDatas[MAX_ENTITIES];

#endif // GLOBALS_H