#include "../include/aspect.h"

Aspect* Aspect_Init(const SDL_Rect* bounds, const SDL_Point* center, double angle, double scale) {
    Aspect* aspect = (Aspect*)malloc(sizeof(Aspect));
    if (!aspect) {
        printf("Aspect_Init: Erreur d'allocation de mémoire pour Aspect\n");
        return NULL;
    }

    if (scale <= 0) {
        scale = 1.0;
    }

    if (!bounds || bounds->w < 0 || bounds->h < 0) {
        printf("Aspect_Init: Erreur bounds invalide\n\t%s\n", SDL_GetError());
        free(aspect);
        return NULL;
    }

    aspect->bounds = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    if (!aspect->bounds) {
        printf("Aspect_Init: Erreur d'allocation de mémoire pour bounds\n\t%s\n", SDL_GetError());
        free(aspect);
        return NULL;
    }
    *(aspect->bounds) = *bounds;

    if (!center) {
        printf("Aspect_Init: Erreur center invalide\n\t%s\n", SDL_GetError());
        free(aspect->bounds);
        free(aspect);
        return NULL;
    }

    aspect->center = (SDL_Point*)malloc(sizeof(SDL_Point));
    if (!aspect->center) {
        printf("Aspect_Init: Erreur d'allocation de mémoire pour center\n\t%s\n", SDL_GetError());
        free(aspect->bounds);
        free(aspect);
        return NULL;
    }
    *(aspect->center) = *center;

    aspect->angle = angle;
    aspect->scale = scale;

    return aspect;
}


SDL_Rect* Aspect_GetScaledBounds(const Aspect* aspect) {

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