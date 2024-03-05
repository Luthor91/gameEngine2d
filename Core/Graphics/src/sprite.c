#include "../include/sprite.h"

/**************************
    Fichier source décrivant les fonctions associé au Sprite : 

    typedef struct Sprite {
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Rect rect;
        SDL_Point*center;
        SDL_Point*pivot;
        double angle;
        double scale;
        char* path;
    } Sprite;

    renderer : permet d'afficher le sprite à l'écran, c'est le renderer de la window
    texture  : texture provenant du sprite
    rect     : forme rectangulaire entourant l'objet, sorte de hitbox
    center   : centre du sprite
    pivot    : centre du sprite, sera utilisé pour définir la rotation autour du-dit pivot
    angle    : angle d'inclinaison du sprite
    scale    : valeur d emise à l'échelle du sprite, permet d'afficher en plus grand ou plus petit l'objet
    path     : source de la texture du sprite, image originelle

***************************/


/**************************
    Initialisation du sprite
***************************/
Sprite* Sprite_Init(SDL_Renderer* renderer, Transform* transform, const char* filepath) {

    if (transform->scale == 0) {
        transform->scale = 1.0;
    }

    Sprite* sprite = malloc(sizeof(Sprite));
   
    sprite->texture = IMG_LoadTexture(renderer, filepath);
    if (!sprite->texture) {
        fprintf(stderr, "Sprite_Init: %s\n", IMG_GetError());
        free(sprite);
        return 0;
    }

    if (!sprite->texture) {
        fprintf(stderr, "Sprite_Init: %s\n", IMG_GetError());
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

    if (!renderer){
        printf("Sprite_RenderStatic: Erreur renderer invalide\n\t%s\n", SDL_GetError());
        return;
    }
    if (!sprite->texture){
        printf("Sprite_RenderStatic: Erreur texture invalide\n\t%s\n", SDL_GetError());
        return;
    }
    if (!sprite->transform->bounds){
        printf("Sprite_RenderStatic: Erreur bounds invalide\n\t%s\n", SDL_GetError());
        return;
    }

    SDL_RenderCopy(renderer, sprite->texture, NULL, Transform_GetScaledBounds(sprite->transform));

}

void Sprite_RenderTransformable(Sprite* sprite, SDL_Renderer* renderer, SDL_RendererFlip flip) {
    if (!renderer){
        printf("Sprite_RenderTransformable: Erreur renderer invalide\n");
        return;
    }
    if (!sprite){
        printf("Sprite_RenderTransformable: Erreur sprite invalide\n");
        return;
    }
    SDL_RenderCopyEx(renderer, sprite->texture, NULL, Transform_GetScaledBounds(sprite->transform), sprite->transform->angle, sprite->transform->center, flip);

}

void Sprites_RenderStatic(Sprite** sprites, int numSprites, SDL_Renderer* renderer) {
    if (!renderer){
        printf("Sprites_RenderStatic: Erreur renderer invalide\n");
        return;
    }
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