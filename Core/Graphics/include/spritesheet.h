#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "sprite.h"
#include "../../Spatial/include/size2d.h"

typedef struct SpriteSheet {
    Sprite** sprites;
    Texture* texture;
    Size2D* tile_size;
    int max_frame;
} SpriteSheet;


SpriteSheet* SpriteSheet_Init(SDL_Renderer* renderer, Texture* texture, Size2D tile_size, int max_frame);

#endif // SPRITESHEET_H