#include "../include/sprite.h"

Sprite* Sprite_Create(SDL_Renderer* renderer, const char* filepath) {

    if (!renderer) {
        fprintf(stderr, "Error renderer doesn't exists\n");
        return 0;
    }

    Sprite* sprite = malloc(sizeof(Sprite));

    sprite->renderer = renderer;
   
    sprite->texture = IMG_LoadTexture(renderer, filepath);

    if (!sprite->texture) {
        fprintf(stderr, "sprite_init: %s\n", IMG_GetError());
        return 0;
    }

    return sprite;
}

void Sprite_Destroy(Sprite* sprite) {
    SDL_DestroyTexture(sprite->texture);
    sprite->texture = NULL;
}

void Sprite_SetRect(Sprite* sprite, SDL_Rect rect) {
    sprite->rect = rect;
}

void Sprite_SetPosition(Sprite* sprite, int x, int y) {
    sprite->rect.x = x;
    sprite->rect.y = y;
}

void Sprite_SetSize(Sprite* sprite, int width, int height) {
    sprite->rect.w = width;
    sprite->rect.h = height;
}

void Sprite_Render(Sprite* sprite) {
    SDL_Rect srcRect = { sprite->rect.x, sprite->rect.y, sprite->rect.w, sprite->rect.h };
    SDL_RenderCopy(sprite->renderer, sprite->texture, NULL, &sprite->rect);
}