#include "../include/transform.h"

Transform* Transform_Init(const SDL_Rect* bounds, const SDL_Point* center, double angle, double scale) {
    Transform* transform = (Transform*)malloc(sizeof(Transform));
    if (!transform) {
        printf("Transform_Init: Erreur d'allocation de mémoire pour Transform\n");
        return NULL;
    }

    if (scale <= 0) {
        scale = 1.0;
    }

    if (!bounds || bounds->w < 0 || bounds->h < 0) {
        printf("Transform_Init: Erreur bounds invalide\n\t%s\n", SDL_GetError());
        free(transform);
        return NULL;
    }

    transform->bounds = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    if (!transform->bounds) {
        printf("Transform_Init: Erreur d'allocation de mémoire pour bounds\n\t%s\n", SDL_GetError());
        free(transform);
        return NULL;
    }
    *(transform->bounds) = *bounds;

    if (!center) {
        printf("Transform_Init: Erreur center invalide\n\t%s\n", SDL_GetError());
        free(transform->bounds);
        free(transform);
        return NULL;
    }

    transform->center = (SDL_Point*)malloc(sizeof(SDL_Point));
    if (!transform->center) {
        printf("Transform_Init: Erreur d'allocation de mémoire pour center\n\t%s\n", SDL_GetError());
        free(transform->bounds);
        free(transform);
        return NULL;
    }
    *(transform->center) = *center;

    transform->angle = angle;
    transform->scale = scale;

    return transform;
}


SDL_Rect* Transform_GetScaledBounds(const Transform* transform) {

    SDL_Rect* bounds = transform->bounds;
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