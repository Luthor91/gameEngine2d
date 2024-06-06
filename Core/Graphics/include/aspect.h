#ifndef ASPECT_H
#define ASPECT_H

#include <SDL2/SDL.h>

typedef struct Aspect {
    SDL_Rect* bounds;
    SDL_Color* color;
    SDL_Point* center;
    double angle;
    double scale;
} Aspect;

Aspect* Aspect_Init(const SDL_Rect* bounds, const SDL_Point* center, double angle, double scale);
SDL_Rect* Aspect_GetScaledBounds(const Aspect* aspect);

#endif // ASPECT_H