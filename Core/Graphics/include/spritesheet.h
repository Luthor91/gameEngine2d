#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SDL2/SDL_thread.h>

#include "frame.h"
#include "sprite.h"

typedef struct SpriteSheet {
    Frame** frames;
    Sprite* sprite;
    int tile_width;
    int tile_height;
    int max_frame;
} SpriteSheet;


SpriteSheet* SpriteSheet_Init(SDL_Renderer* renderer, Sprite* sprite, int tile_width, int tile_height, int max_frame);

#endif // SPRITESHEET_H