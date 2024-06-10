#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL_thread.h>

#include "animated_frame.h"
#include "sprite.h"

typedef struct Animation {
    AnimatedFrame** frames;
    int speed;
    int lastFrameTime;
    int currentFrame;
    int max_frame;
} Animation;

typedef struct Animation_Wrapper {
    Animation* animation;
    SDL_Renderer* renderer;
    int repeat;
} Animation_Wrapper;

typedef struct AnimatedFrame {
    int id;
    Size2d* origin; // Position de la Frame dans le spritesheet
    SDL_Rect* target; // Position à l'écran
    SDL_Texture* texture;
    float delay;
} AnimatedFrame;

Animation* Animation_Init(SDL_Renderer* renderer, Sprite* sprite, SDL_Rect* target, int tile_width, int tile_height, int max_frame, int speed);

void Animation_Delay(Animation* animation);
void Animation_Render(Animation* animation, SDL_Renderer* renderer);
int Animation_Render_Thread(void *data);

#endif // ANIMATION_H