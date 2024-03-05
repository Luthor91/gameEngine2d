#include <SDL2/SDL.h>
#include "../include/transform.h"

Transform* Transform_Init(SDL_Rect* bounds, SDL_Point* center, double angle, double scale) {
    
    Transform* transform = malloc(sizeof(Transform));

    if (scale == 0) {
        scale = 1.0;
    }

    transform->bounds = bounds;
    transform->center = center;
    transform->angle = angle;
    transform->scale = scale;

    return transform;

}

SDL_Rect* Transform_GetScaledBounds(const Transform* transform) {

    SDL_Rect* bounds = malloc(sizeof(SDL_Rect));
    bounds->w = transform->bounds->w;
    bounds->h = transform->bounds->h;

    int new_w = (int)(bounds->w * transform->scale);
    int new_h = (int)(bounds->h * transform->scale);
    if (new_w >= 1) {
        bounds->w = new_w;
    }
    if (new_h >= 1) {
        bounds->h = new_h;
    }

    return bounds;

}