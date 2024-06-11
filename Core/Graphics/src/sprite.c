#include "../include/sprite.h"

Sprite* Sprite_Init(SDL_Renderer* renderer, Transform* transform, Texture* texture) {

    if (!transform) {
        transform = Transform_Init(&(Point2D){0, 0}, &(Size2D){0, 0}, &(Point2D){0, 0}, 0.0, 0.0);
    }

    Sprite* sprite = malloc(sizeof(Sprite));
    sprite->texture = texture;
    sprite->transform = transform;

    return sprite;
}

void Sprite_Destroy(Sprite* sprite) {
    SDL_DestroyTexture(sprite->texture);
    sprite->texture = NULL;
}