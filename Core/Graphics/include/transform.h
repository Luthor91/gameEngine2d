#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect* bounds;
    SDL_Color* color;
    SDL_Point* center;
    double angle;
    double scale;
} Transform;

Transform* Transform_Init(SDL_Rect* bounds, SDL_Point* center, double angle, double scale);
SDL_Rect* Transform_GetScaledBounds(const Transform* transform);

#endif // TRANSFORM_H