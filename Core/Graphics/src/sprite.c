#include "../include/sprite.h"

/**************************
    Fichier source décrivant les fonctions associé au Sprite : 

    typedef struct Sprite {
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Rect rect;
        SDL_Point center;
        SDL_Point pivot;
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

Sprite* Sprite_Init(SDL_Renderer* renderer, const char* filepath, SDL_Rect rect, SDL_Point pos_center, double scale, double angle) {

    if (!renderer) {
        fprintf(stderr, "Error renderer doesn't exists\n");
        return 0;
    }

    if (scale == 0) {
        scale = 1.0;
    }

    Sprite* sprite = malloc(sizeof(Sprite));
   
    sprite->texture = IMG_LoadTexture(renderer, filepath);
    if (!sprite->texture) {
        fprintf(stderr, "Sprite_Init: %s\n", IMG_GetError());
        return 0;
    }

    sprite->renderer = renderer;
    if (!sprite->texture) {
        fprintf(stderr, "Sprite_Init: %s\n", IMG_GetError());
        return 0;
    }

    sprite->path = (char*) malloc(strlen(filepath) + 1);
    if (sprite->path == NULL) {
        fprintf(stderr, "Sprite_Init:Erreur d'allocation de mémoire pour le chemin du sprite\n");
        return 0;
    }

    if (strcpy(sprite->path, filepath) == NULL) {
        fprintf(stderr, "Sprite_Init: Erreur de copie du chemin dans le sprite\n");
        return 0;
    }
    
    int new_w = (int)(rect.w * scale);
    int new_h = (int)(rect.h * scale);

    if (new_w >= 1) {
        rect.w = (int)new_w;
    }
    if (new_h >= 1) {
        rect.h = (int)new_h;
    }

    sprite->center = pos_center;
    sprite->rect = rect;
    sprite->scale = scale;
    sprite->angle = angle;

    return sprite;
}

/**************************
    Affectation des valeurs au sprite
***************************/

void Sprite_SetRectangle(Sprite* sprite, SDL_Rect rect) {

    int min_x = rect.x;
    int min_y = rect.y;
    int max_x = rect.w + rect.x;
    int max_y = rect.y + rect.y;

    SDL_Point center = (SDL_Point){max_x-min_x, max_y-min_y };
    sprite->center = center;
    sprite->rect = rect;
}

void Sprite_SetScale(Sprite* sprite, double scale) {
    if (scale == 0.0) {
        return;
    }
    sprite->scale = scale;

    Sprite_UpdateCenter(sprite);
}

void Sprite_SetPosition(Sprite* sprite, int x, int y) {
    sprite->rect.x = x;
    sprite->rect.y = y;
}

void Sprite_SetCenter(Sprite* sprite, int x, int y) {

    SDL_Point center = (SDL_Point){x, y };
    sprite->center = center;
}

void Sprite_SetSize(Sprite* sprite, int width, int height) {
    sprite->rect.w = width;
    sprite->rect.h = height;
}

void Sprite_SetRenderer(Sprite* sprite, SDL_Renderer* renderer) {
    sprite->renderer = renderer; 
}

/**************************
    Calcul des attributs du sprite
***************************/

void Sprite_UpdateCenter(Sprite* sprite) {

    int min_x = sprite->rect.x;
    int min_y = sprite->rect.y;
    int max_x = sprite->rect.w + sprite->rect.x;
    int max_y = sprite->rect.y + sprite->rect.y;

    SDL_Point center = (SDL_Point){max_x-min_x, max_y-min_y };
    sprite->center = center;

}

void Sprite_UpdateRect(Sprite* sprite) {

    int new_w = (int)(sprite->rect.w * sprite->scale);
    int new_h = (int)(sprite->rect.h * sprite->scale);

    if (new_w >= 1) {
        sprite->rect.w = (int)new_w;
    }
    if (new_h >= 1) {
        sprite->rect.h = (int)new_h;
    }

}

/**************************
    Affichage du sprite
***************************/

void Sprite_RenderStatic(Sprite* sprite, SDL_Renderer* renderer) {
    if (!renderer){
        printf("Sprite_RenderStatic: Erreur renderer invalide\n");
        return;
    }
    if (!sprite){
        printf("Sprite_RenderStatic: Erreur sprite invalide\n");
        return;
    }
    
    SDL_RenderCopy(renderer, sprite->texture, NULL, &sprite->rect);
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
    SDL_RenderCopyEx(renderer, sprite->texture, NULL, &sprite->rect, sprite->angle, &sprite->center, flip);
}

void Sprites_RenderStatic(Sprite** sprites, int numSprites, SDL_Renderer* renderer) {
    if (!renderer){
        printf("Sprites_RenderStatic: Erreur renderer invalide\n");
        return;
    }
    for (int i = 0; i < numSprites; i++) {
        SDL_RenderCopy(renderer, sprites[i]->texture, NULL, &sprites[i]->rect);
    }
}

void Sprites_RenderTransformable(Sprite** sprites, int numSprites, SDL_Renderer* renderer, SDL_RendererFlip flip ) {
    for (int i = 0; i < numSprites; i++) {
        SDL_RenderCopyEx(renderer, sprites[i]->texture, NULL, &sprites[i]->rect, sprites[i]->angle, &sprites[i]->center, flip);
    }
}

void Sprite_Destroy(Sprite* sprite) {
    SDL_DestroyTexture(sprite->texture);
    sprite->texture = NULL;
}