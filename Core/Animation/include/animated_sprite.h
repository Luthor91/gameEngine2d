#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SDL2/SDL_thread.h>

#include "frame.h"
#include "sprite.h"
#include "aspect.h"

typedef struct AnimatedSprite {
    Aspect* start;
    Aspect* end;
    Sprite* sprite;
    int speed;
    int currentFrame;
    int max_frame;
    int lastUpdateTime;
} AnimatedSprite;

typedef struct AnimatedSpriteManager {
    AnimatedSprite** animated_sprites;
    int max_animated_sprite;
    int index;
} AnimatedSpriteManager;

AnimatedSpriteManager* AnimatedSpriteManager_Init();
AnimatedSprite* AnimatedSprite_Init(SDL_Renderer* renderer, Sprite* sprite, Aspect* start, Aspect* end, int speed);

void AnimatedSpriteManager_Add(AnimatedSpriteManager* manager, AnimatedSprite* animated_sprite);

void AnimatedSprite_Render(AnimatedSprite* animated_sprite, SDL_Renderer* renderer);
void AnimatedSpriteManager_Render(AnimatedSpriteManager* animated_sprite, SDL_Renderer* renderer);

#endif // ANIMATED_SPRITE_H