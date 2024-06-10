#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL_thread.h>

#include "animation_settings.h"
#include "animation_frame.h"

typedef struct StaticAnimation  {
    AnimationFrame** frames;
    AnimationSettings* animation_settings;
} StaticAnimation;

typedef struct StaticAnimationManager {
    StaticAnimation** dynamic_animation;
    int max_animated_sprite;
    int index;
} StaticAnimationManager;

Animation* Animation_Init(SDL_Renderer* renderer, Sprite* sprite, SDL_Rect* target, int tile_width, int tile_height, int max_frame, int speed);
void Animation_Render(Animation* animation, SDL_Renderer* renderer);

AnimatedFrame* Frame_Init(SDL_Rect* origin, SDL_Rect* target, SDL_Texture* texture, float delay, int id);
void Frame_Render(AnimatedFrame* frame, SDL_Renderer* renderer);
void Frame_Render_Debug(AnimatedFrame* frame, SDL_Renderer* renderer);

#endif // ANIMATION_H