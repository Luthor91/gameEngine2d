#include "../include/sprite.h"

Sprite* Sprite_Create(SDL_Renderer* renderer, const char* filepath) {

    if (!renderer) {
        fprintf(stderr, "Error renderer doesn't exists\n");
        return 0;
    }

    Sprite* sprite = malloc(sizeof(Sprite));
   
    sprite->texture = IMG_LoadTexture(renderer, filepath);
    if (!sprite->texture) {
        fprintf(stderr, "Sprite_Create: %s\n", IMG_GetError());
        return 0;
    }

    sprite->renderer = renderer;
    if (!sprite->texture) {
        fprintf(stderr, "Sprite_Create: %s\n", IMG_GetError());
        return 0;
    }

    sprite->path = (char*) malloc(strlen(filepath) + 1);
    if (sprite->path == NULL) {
        fprintf(stderr, "Sprite_Create:Erreur d'allocation de mémoire pour le chemin du sprite\n");
        return 0;
    }

    if (strcpy(sprite->path, filepath) == NULL) {
        fprintf(stderr, "Sprite_Create: Erreur de copie du chemin dans le sprite\n");
        return 0;
    }

    sprite->scale = 1.0;

    return sprite;
}

void Sprite_Destroy(Sprite* sprite) {
    SDL_DestroyTexture(sprite->texture);
    sprite->texture = NULL;
}

void Sprite_SetScale(Sprite* sprite, double scale) {
    if (scale == 0.0) {
        return;
    }
    sprite->scale = scale;
}

void Sprite_SetRectangle(Sprite* sprite, SDL_Rect rect) {

    int min_x = rect.x;
    int min_y = rect.y;
    int max_x = rect.w + rect.x;
    int max_y = rect.y + rect.y;

    SDL_Point center = (SDL_Point){max_x-min_x, max_y-min_y };
    sprite->center = center;
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

void Sprite_SetRenderer(Sprite* sprite, SDL_Renderer* renderer) {
    sprite->renderer = renderer;
    
}

void Sprite_Render(Sprite* sprite) {

    SDL_Rect newRect = Sprite_CalcScale(sprite->rect, sprite->scale);

    SDL_RenderCopy(sprite->renderer, sprite->texture, NULL, &newRect);
}

// Copie une texture sur chaque renderer d'un tableau
void Sprite_RenderAll(Sprite** sprites, int numSprites, SDL_Renderer* renderer) {
    for (int i = 0; i < numSprites; i++) {
        
        SDL_Rect newRect = Sprite_CalcScale(sprites[i]->rect, sprites[i]->scale);
        SDL_RenderCopy(renderer, sprites[i]->texture, NULL, &newRect);
    }
}

void Sprite_RenderRotAll(Sprite** sprites, int numSprites, SDL_Renderer* renderer) {
    for (int i = 0; i < numSprites; i++) {
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
        SDL_Rect newRect = Sprite_CalcScale(sprites[i]->rect, sprites[i]->scale);
        SDL_RenderCopyEx(renderer, sprites[i]->texture, NULL, &newRect, 60, &sprites[i]->center, flip);
    }
}

        

SDL_Rect Sprite_CalcScale(SDL_Rect rect, double scale) {
    int new_w = (int)(rect.w * scale);
    int new_h = (int)(rect.h * scale);

    if (new_w >= 1) {
        rect.w = (int)new_w;
    }
    if (new_h >= 1) {
        rect.h = (int)new_h;
    }

    return rect;

}