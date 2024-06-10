#ifndef ANIMATED_SPRITESHEET_H
#define ANIMATED_SPRITESHEET_H

#include <SDL2/SDL_thread.h>

#include "frame.h"
#include "spritesheet.h"

typedef struct DynamicAnimation {
    AnimationFrame** startFrames;  // Frames de départ de l'animation
    AnimationFrame** endFrames;    // Frames d'arrivée de l'animation
    AnimationSettings* animation_settings;
} DynamicAnimation;

typedef struct DynamicAnimationManager {
    DynamicAnimation** dynamic_animation;
    int max_animated_sprite;
    int index;
} DynamicAnimationManager;

AnimatedSpriteSheet* AnimatedSpriteSheet_Init(SDL_Renderer* renderer, SpriteSheet* spritesheet, Aspect* start, Aspect* end, int speed, int repeat);
void AnimatedSpriteSheet_Delay(AnimatedSpriteSheet* animation_sprite);
void AnimatedSpriteSheet_Render(AnimatedSpriteSheet* animation_sprite, SDL_Renderer* renderer);

#endif // ANIMATED_SPRITESHEET_H