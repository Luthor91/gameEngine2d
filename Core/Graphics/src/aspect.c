#include "../include/aspect.h"

Aspect* Aspect_Init(SDL_Rect* bounds, SDL_Point* center, double angle, double scale) {
    Aspect* aspect = (Aspect*)malloc(sizeof(Aspect));
    if (!aspect) {
        printf("Erreur d'allocation de mémoire pour Aspect\n");
        return NULL;
    }

    aspect->bounds = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    if (!aspect->bounds) {
        printf("Erreur d'allocation de mémoire pour bounds\n");
        free(aspect);
        return NULL;
    }
    aspect->bounds = bounds;
    
    aspect->center = (SDL_Point*)malloc(sizeof(SDL_Point));
    if (!aspect->center) {
        printf("Erreur d'allocation de mémoire pour center\n");
        free(aspect->bounds);
        free(aspect);
        return NULL;
    }
    aspect->center = center;
    aspect->angle = angle;
    aspect->scale = scale;

    return aspect;
}

SDL_Rect* Aspect_GetScaledBounds(Aspect* aspect) {

    SDL_Rect* bounds = aspect->bounds;
    bounds->w = aspect->bounds->w;
    bounds->h = aspect->bounds->h;

    int new_w = (int)(bounds->w * aspect->scale);
    int new_h = (int)(bounds->h * aspect->scale);
    if (new_w >= 1) {
        bounds->w = new_w;
    }
    if (new_h >= 1) {
        bounds->h = new_h;
    }

    return bounds;

}