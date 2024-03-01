#include "../include/label.h"

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

Label* Label_Init(SDL_Renderer* renderer, const char* font, int size_font, SDL_Color color_font, const char* text, int pos_x, int pos_y, int width, int height, int center_x, int center_y, double scale, double angle) {
    
    TTF_Font* ttf_font = TTF_OpenFont(font, size_font);

    SDL_Color color = color_font;

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(ttf_font, text, color); 

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate 
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect

    return label;
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
    SDL_RenderCopy(renderer, sprite->texture, NULL, &sprite->rect);
}

void Sprite_RenderTransformable(Sprite* sprite, SDL_Renderer* renderer, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(renderer, sprite->texture, NULL, &sprite->rect, sprite->angle, &sprite->center, flip);
}

void Sprites_RenderStatic(Sprite** sprites, int numSprites, SDL_Renderer* renderer) {
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