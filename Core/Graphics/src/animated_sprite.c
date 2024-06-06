// gcc -I/usr/include/SDL2 -o AnimatedSprite_test Examples/SDL2/AnimatedSprite_test.c Core/Graphics/src/sprite.c Core/Graphics/src/tilemap.c Core/Graphics/src/aspect.c Core/Graphics/src/window.c Core/Graphics/src/frame.c -lSDL2 -lSDL2_image -lm && ./AnimatedSprite_test

#include "../include/animated_sprite.h"

AnimatedSpriteManager* AnimatedSpriteManager_Init(int max_anim) {
    AnimatedSpriteManager* manager = (AnimatedSpriteManager*)malloc(sizeof(AnimatedSpriteManager));

    manager->max_animated_sprite = max_anim;
    manager->index = 0;
    manager->animated_sprites = (AnimatedSprite**)malloc(max_anim * sizeof(AnimatedSprite*));

    for (int i = 0; i < max_anim; i++) {
        manager->animated_sprites[i] = NULL;
    }
    
    return manager;
}

// speed : temps total de l'animation en milisecondes
AnimatedSprite* AnimatedSprite_Init(SDL_Renderer* renderer, Sprite* sprite, Aspect* start, Aspect* end, int speed) {
    if (!sprite || !sprite->texture) {
        printf("AnimatedSprite_Init: Erreur lors de la création de la texture\n");
        return NULL;
    }

    AnimatedSprite* animated_sprite = (AnimatedSprite*)malloc(sizeof(AnimatedSprite));
    if (!animated_sprite) {
        printf("AnimatedSprite_Init: Erreur lors de l'allocation de mémoire pour l'animation\n");
        SDL_DestroyTexture(sprite->texture);
        return NULL;
    }

    animated_sprite->speed = speed;
    animated_sprite->start = start;
    animated_sprite->end = end;
    animated_sprite->sprite = sprite;
    animated_sprite->lastUpdateTime = SDL_GetTicks();  // Initialiser le temps de la dernière mise à jour
    return animated_sprite;
}

void AnimatedSpriteManager_Add(AnimatedSpriteManager* manager, AnimatedSprite* animated_sprite) {
    if (manager->index < manager->max_animated_sprite) {
        manager->animated_sprites[manager->index] = animated_sprite;
        manager->index++;
    } else {
        printf("AnimatedSpriteManager_Add: Impossible d'ajouter plus d'animations, limite atteinte\n");
    }
}

void AnimatedSprite_Render(AnimatedSprite* animated_sprite, SDL_Renderer* renderer) {
    int current_time = SDL_GetTicks();
    int elapsed_time = current_time - animated_sprite->lastUpdateTime;

    // Si le temps écoulé est supérieur à la vitesse de l'animation, remettre à zéro
    if (elapsed_time >= animated_sprite->speed) {
        elapsed_time = elapsed_time % animated_sprite->speed;  // Réinitialiser le temps écoulé
        animated_sprite->lastUpdateTime = current_time - elapsed_time;  // Mettre à jour lastUpdateTime
    }

    // Progression proportionnelle à l'animation
    float progress = (float)elapsed_time / animated_sprite->speed;

    // Calculer les positions interpolées entre start et end
    SDL_Rect interpolated_position;
    interpolated_position.x = animated_sprite->start->bounds->x + (int)((animated_sprite->end->bounds->x - animated_sprite->start->bounds->x) * progress);
    interpolated_position.y = animated_sprite->start->bounds->y + (int)((animated_sprite->end->bounds->y - animated_sprite->start->bounds->y) * progress);
    interpolated_position.w = animated_sprite->start->bounds->w + (int)((animated_sprite->end->bounds->w - animated_sprite->start->bounds->w) * progress);
    interpolated_position.h = animated_sprite->start->bounds->h + (int)((animated_sprite->end->bounds->h - animated_sprite->start->bounds->h) * progress);

    // Render the current frame
    SDL_RenderCopy(renderer, animated_sprite->sprite->texture, NULL, &interpolated_position);
}

void AnimatedSpriteManager_Render(AnimatedSpriteManager* manager, SDL_Renderer* renderer) {
    for (int i = 0; i < manager->index; i++) {
        if (manager->animated_sprites[i] != NULL) {
            AnimatedSprite_Render(manager->animated_sprites[i], renderer);
        }
    }
}

void AnimatedSpriteManager_Destroy(AnimatedSpriteManager* manager) {
    if (manager) {
        if (manager->animated_sprites) {
            for (int i = 0; i < manager->max_animated_sprite; i++) {
                if (manager->animated_sprites[i]) {
                    free(manager->animated_sprites[i]);
                }
            }
            free(manager->animated_sprites);
        }
        free(manager);
    }
}