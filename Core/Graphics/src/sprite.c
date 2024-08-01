#include "../include/sprite.h"

Sprite* Sprite_Init(Transform* transform, Texture* texture) {

    if (!texture) {
        fprintf(stderr, "Sprite_Init: texture invalid, default value used\n");
        texture = Texture_Init(NULL, "Assets/Default/DefaultObject.png");
    }

    if (!transform) {
        fprintf(stderr, "Sprite_Init: transform invalid, default value used\n");
        transform = Transform_Init(NULL, &(Size2D){DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT}, NULL, 0, 0);
    }

    Sprite* sprite = (Sprite*)malloc(sizeof(Sprite));
    if (!sprite) {
        fprintf(stderr, "Sprite_Init: Memory allocation failed for Sprite.\n");
        return NULL;
    }

    sprite->transform = transform;
    sprite->texture = texture;

    return sprite;
}

void Sprite_Set(Sprite* sprite, const char* params) {
    Object_Set(sprite, params, "Sprite");
}

void Sprite_SetPosition(Sprite* sprite, int x, int y) {

    if (x < 0) {
        x = sprite->transform->position->x;
    }

    if (y < 0) {
        y = sprite->transform->position->y;
    }
    
    sprite->transform->position->x = x;
    sprite->transform->position->y = y;

}

void Sprite_SetSize(Sprite* sprite, int width, int height) {

    if (width < 0) {
        width = sprite->transform->size->width;
    }

    if (height < 0) {
        height = sprite->transform->size->height;
    }
    
    sprite->transform->size->width = width;
    sprite->transform->size->height = height;

}

void Sprite_Destroy(Sprite* sprite) {
    SDL_DestroyTexture(sprite->texture->sdl_texture);
    sprite->texture = NULL;
}
