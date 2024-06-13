#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include "../../Spatial/include/transform.h"
#include "../../Graphics/include/texture.h"

typedef struct Sprite {
    int id;
    Texture* texture;
    Transform* transform;
} Sprite;

/**************************
    Initialisation du sprite
***************************/

Sprite* Sprite_Init(SDL_Renderer* renderer, Transform* transform, Texture* texture);
void Sprite_Destroy(Sprite* sprite);

#endif