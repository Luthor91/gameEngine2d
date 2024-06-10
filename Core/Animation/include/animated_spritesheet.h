#ifndef ANIMATED_SPRITESHEET_H
#define ANIMATED_SPRITESHEET_H

#include <SDL2/SDL_thread.h>

#include "frame.h"
#include "spritesheet.h"

typedef struct AnimatedSpriteSheet {
    Aspect* start;
    Aspect* end;
    SpriteSheet* spritesheet;
    int speed;
    int currentFrame;
    int max_frame;
    int lastFrameTime;
    int animationStartTime;
    int repeat;
} AnimatedSpriteSheet;

AnimatedSpriteSheet* AnimatedSpriteSheet_Init(SDL_Renderer* renderer, SpriteSheet* spritesheet, Aspect* start, Aspect* end, int speed, int repeat);
void AnimatedSpriteSheet_Delay(AnimatedSpriteSheet* animation_sprite);
void AnimatedSpriteSheet_Render(AnimatedSpriteSheet* animation_sprite, SDL_Renderer* renderer);

#endif // ANIMATED_SPRITESHEET_H