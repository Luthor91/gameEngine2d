#include "../include/transform.h"

Transform* Transform_Init(SDL_Rect* bounds, SDL_Point* center, double angle, double scale) {
    
    Transform* transform = malloc(sizeof(Transform));

    if (scale <= 0) {
        scale = 1.0;
    }

    transform->bounds = bounds;
    transform->center = center;
    transform->angle = angle;
    transform->scale = scale;

    if (!transform->bounds){
        printf("Transform_Init: Erreur bounds invalide\n\t%s\n", SDL_GetError());
        free(transform);
        return NULL;
    }
    if (transform->bounds->w < 0){
        printf("Transform_Init: Erreur largeur invalide\n\t%s\n", SDL_GetError());
        free(transform);
        return NULL;
    }
    if (transform->bounds->h < 0){
        printf("Transform_Init: Erreur hauteur invalide\n\t%s\n", SDL_GetError());
        free(transform);
        return NULL;
    }

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