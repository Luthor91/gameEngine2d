// gcc -I/usr/include/SDL2 -o AnimatedSpriteSheetSheet_test Examples/SDL2/AnimatedSpriteSheetSheet_test.c Core/Graphics/src/sprite.c Core/Graphics/src/tilemap.c Core/Graphics/src/aspect.c Core/Graphics/src/window.c Core/Graphics/src/frame.c -lSDL2 -lSDL2_image -lm && ./AnimatedSpriteSheetSheet_test

#include "../include/animated_spritesheet.h"




/**
 * speed : temps total de l'animation en milisecondes
*/
AnimatedSpriteSheet* AnimatedSpriteSheet_Init(SDL_Renderer* renderer, SpriteSheet* spritesheet, Aspect* start, Aspect* end, int speed, int repeat) {
    if (!spritesheet) {
        printf("AnimatedSpriteSheet_Init: Erreur lors de la création de la texture\n");
        return NULL;
    }

    AnimatedSpriteSheet* animated_spritesheet = (AnimatedSpriteSheet*)malloc(sizeof(AnimatedSpriteSheet));
    if (!animated_spritesheet) {
        printf("AnimatedSpriteSheet_Init: Erreur lors de l'allocation de mémoire pour l'animation\n");
        return NULL;
    }

    animated_spritesheet->speed = speed;
    animated_spritesheet->repeat = repeat;
    animated_spritesheet->start = start;
    animated_spritesheet->end = end;
    animated_spritesheet->spritesheet = spritesheet;
    animated_spritesheet->max_frame = spritesheet->max_frame;
    animated_spritesheet->animationStartTime = SDL_GetTicks();

    for (size_t i = 0; i < spritesheet->max_frame; i++){
        animated_spritesheet->spritesheet->frames[i]->delay = (float) speed / spritesheet->max_frame;
    }

    return animated_spritesheet;
}

void AnimatedSpriteSheet_Render(AnimatedSpriteSheet* animated_spritesheet, SDL_Renderer* renderer) {
    int current_time = SDL_GetTicks();
    int elapsed_time = current_time - animated_spritesheet->lastFrameTime;

    // Gestion du timing des frames
    if (elapsed_time >= animated_spritesheet->spritesheet->frames[animated_spritesheet->currentFrame]->delay) {
        animated_spritesheet->currentFrame++;
        animated_spritesheet->lastFrameTime = current_time;

        if (animated_spritesheet->currentFrame >= animated_spritesheet->spritesheet->max_frame) {
            animated_spritesheet->currentFrame = 0;
        }
    }

    // Calcul de la progression totale de l'animation
    int total_elapsed_time = current_time - animated_spritesheet->animationStartTime;
    float overall_progress = (float)total_elapsed_time / animated_spritesheet->speed;

    SDL_Rect interpolated_position;

    if (overall_progress > 1.0f) {
        if (animated_spritesheet->repeat == 0) {
            overall_progress = 1.0f;
        } else {
            overall_progress = 0.0f;
            animated_spritesheet->animationStartTime = SDL_GetTicks();
            interpolated_position = *animated_spritesheet->start->bounds;
        } 
    }

    Frame* curr_frame = animated_spritesheet->spritesheet->frames[animated_spritesheet->currentFrame];
    Frame* next_frame = animated_spritesheet->spritesheet->frames[(animated_spritesheet->currentFrame + 1) % animated_spritesheet->spritesheet->max_frame];

    // Calculer les positions interpolées entre start et end avec la progression globale de l'animation
    interpolated_position.x = animated_spritesheet->start->bounds->x + (int)((animated_spritesheet->end->bounds->x - animated_spritesheet->start->bounds->x) * overall_progress);
    interpolated_position.y = animated_spritesheet->start->bounds->y + (int)((animated_spritesheet->end->bounds->y - animated_spritesheet->start->bounds->y) * overall_progress);
    interpolated_position.w = animated_spritesheet->start->bounds->w + (int)((animated_spritesheet->end->bounds->w - animated_spritesheet->start->bounds->w) * overall_progress);
    interpolated_position.h = animated_spritesheet->start->bounds->h + (int)((animated_spritesheet->end->bounds->h - animated_spritesheet->start->bounds->h) * overall_progress);

    SDL_RenderCopy(renderer, curr_frame->texture, NULL, &interpolated_position);
}