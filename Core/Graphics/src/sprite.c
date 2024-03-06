#include "../include/sprite.h"

/**************************
    Initialisation du sprite
***************************/
Sprite* Sprite_Init(SDL_Renderer* renderer, Transform* transform, const char* filepath) {

    if (!transform) {
        printf("Sprite_Init: Warning, transform vide, transform par défaut défini\n");
        transform = Transform_Init(&(SDL_Rect){0, 0, 0, 0}, &(SDL_Point){0, 0}, 0.0, 1.0);
    }

    Sprite* sprite = malloc(sizeof(Sprite));
   
    sprite->texture = IMG_LoadTexture(renderer, filepath);
    if (!sprite->texture) {
        fprintf(stderr, "Sprite_Init: %s\n", IMG_GetError());
        free(sprite);
        return 0;
    }

    sprite->path = (char*) malloc(strlen(filepath) + 1);
    if (sprite->path == NULL) {
        fprintf(stderr, "Sprite_Init:Erreur d'allocation de mémoire pour le chemin du sprite\n");
        free(sprite);
        return 0;
    }

    if (strcpy(sprite->path, filepath) == NULL) {
        fprintf(stderr, "Sprite_Init: Erreur de copie du chemin dans le sprite\n");
        return 0;
    }

    sprite->transform = transform;

    return sprite;
}

/**************************
    Affichage du sprite
***************************/

void Sprite_RenderStatic(Sprite* sprite, SDL_Renderer* renderer) {
    if (!renderer || !sprite->texture){
        printf("Sprite_RenderStatic: Erreur pendant l'affichage\n\t%s\n", SDL_GetError());
        return;
    }

    SDL_RenderCopy(renderer, sprite->texture, NULL, Transform_GetScaledBounds(sprite->transform));

}

void Sprite_RenderTransformable(Sprite* sprite, SDL_Renderer* renderer, SDL_RendererFlip flip) {
    if (!renderer || !sprite->texture){
        printf("Sprite_RenderStatic: Erreur pendant l'affichage\n\t%s\n", SDL_GetError());
        return;
    }

    SDL_RenderCopyEx(renderer, sprite->texture, NULL, Transform_GetScaledBounds(sprite->transform), sprite->transform->angle, sprite->transform->center, flip);

}

void Sprites_RenderStatic(Sprite** sprites, int numSprites, SDL_Renderer* renderer) {
    for (int i = 0; i < numSprites; i++) {
        SDL_RenderCopy(renderer, sprites[i]->texture, NULL, Transform_GetScaledBounds(sprites[i]->transform));
    }
}

void Sprites_RenderTransformable(Sprite** sprites, int numSprites, SDL_Renderer* renderer, SDL_RendererFlip flip ) {
    for (int i = 0; i < numSprites; i++) {
        SDL_RenderCopyEx(renderer, sprites[i]->texture, NULL, Transform_GetScaledBounds(sprites[i]->transform), sprites[i]->transform->angle, sprites[i]->transform->center, flip);
    }
}

void Sprite_Destroy(Sprite* sprite) {
    SDL_DestroyTexture(sprite->texture);
    sprite->texture = NULL;
}