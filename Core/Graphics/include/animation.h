#ifndef ANIMATION_H
#define ANIMATION_H

#include "frame.h"
#include "sprite.h"

typedef struct Animation {
    Frame** frames;
    int speed;
    int lastFrameTime;
    int currentFrame;
    int max_sprite;
} Animation;

Animation* Animation_Init(SDL_Renderer* renderer, Sprite* sprite, int tile_width, int tile_height, int max_sprite, int speed);

void Animation_Delay(Animation* animation);
void Animation_Render(Animation* animation, SDL_Renderer* renderer);



#endif // ANIMATION_H