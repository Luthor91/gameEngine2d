#include "../include/sprite.h"

/**************************
    Initialisation du sprite
***************************/
Sprite* Sprite_Init(SDL_Renderer* renderer, Aspect* aspect, const char* filepath) {

    if (!aspect) {
        aspect = Aspect_Init(&(SDL_Rect){0, 0, 0, 0}, &(SDL_Point){0, 0}, 0.0, 0.0);
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

    sprite->aspect = aspect;

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

    SDL_RenderCopy(renderer, sprite->texture, NULL, Aspect_GetScaledBounds(sprite->aspect));

}

void Sprite_Render(Sprite* sprite, SDL_Renderer* renderer, SDL_RendererFlip flip) {
    if (!renderer || !sprite->texture){
        printf("Sprite_RenderStatic: Erreur pendant l'affichage\n\t%s\n", SDL_GetError());
        return;
    }

    SDL_RenderCopyEx(renderer, sprite->texture, NULL, Aspect_GetScaledBounds(sprite->aspect), sprite->aspect->angle, sprite->aspect->center, flip);

}

void Sprite_RenderCut(Sprite* sprite, SDL_Renderer* renderer, SDL_Rect* src) {
    if (!renderer || !sprite->texture){
        printf("Sprite_RenderStatic: Erreur pendant l'affichage\n\t%s\n", SDL_GetError());
        return;
    }

    SDL_RenderCopy(renderer, sprite->texture, src, Aspect_GetScaledBounds(sprite->aspect));

}

void Sprites_RenderAspectable(Sprite** sprites, int numSprites, SDL_Renderer* renderer, SDL_RendererFlip flip ) {
    for (int i = 0; i < numSprites; i++) {
        SDL_RenderCopyEx(renderer, sprites[i]->texture, NULL, Aspect_GetScaledBounds(sprites[i]->aspect), sprites[i]->aspect->angle, sprites[i]->aspect->center, flip);
    }
}

void Sprite_Destroy(Sprite* sprite) {
    SDL_DestroyTexture(sprite->texture);
    sprite->texture = NULL;
}