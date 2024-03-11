// gcc -I/usr/include/SDL2 -o animation_test Examples/SDL2/animation_test.c Core/Graphics/src/sprite.c Core/Graphics/src/tilemap.c Core/Graphics/src/transform.c Core/Graphics/src/window.c -lSDL2 -lSDL2_image -lm && ./animation_test

#include "../include/animation.h"

Animation* Animation_Init(SDL_Renderer* renderer, Sprite* sprite, int tile_width, int tile_height, int max_sprite, int speed) {

    if (!sprite->texture) {
        printf("Animation_Init: Erreur lors de la création de la texture\n");
        return NULL;
    }
   
    int num_cols = sprite->transform->bounds->w / tile_width;
    int num_rows = sprite->transform->bounds->h / tile_height;

    Animation* animation = (Animation*)malloc(sizeof(Animation));
    if (!animation) {
        printf("Animation_Init: Erreur lors de l'allocation de mémoire pour l'animation\n");
        SDL_DestroyTexture(sprite->texture);
        return NULL;      
    }

    animation->max_sprite = max_sprite;        
    animation->speed = speed;

    Frame** frames = (Frame**)malloc(num_cols * num_rows * sizeof(Frame*));
    int id = 0;

    for (int y = 0; y < num_cols; y++) {
        for (int x = 0; x < num_rows; x++) {
            if (id >=  max_sprite) {
                break;
            }

            Frame* frame = (Frame*)malloc(sizeof(Frame));
            if (!frame) {
                printf("Animation_Init: Error init frame\n");
                return NULL;
            }
             
             frame->bounds = &(SDL_Rect) {x * tile_width, y * tile_height, tile_width, tile_height};

printf("tst\n");
            SDL_Texture* frame_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, tile_width, tile_height);
             
            SDL_SetRenderTarget(renderer, frame_texture);
            SDL_RenderCopy(renderer, sprite->texture, frame->bounds, NULL);
            SDL_SetRenderTarget(renderer, NULL);

            frame->texture = frame_texture;
            frame->id = id;

            frames[id] = frame;
            id++;
        }
    }
    animation->frames = frames;
    return animation;
}

void Animation_Delay(Animation* animation) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - animation->lastFrameTime > animation->speed) {
        animation->currentFrame = (animation->currentFrame + 1) % animation->max_sprite;
        animation->lastFrameTime = currentTime;
    }
}

void Animation_Render(Animation* animation, SDL_Renderer* renderer) {

    if (animation->currentFrame  >= animation->max_sprite) {
        animation->currentFrame = 0;
    }
    
    Frame* curr_frame = animation->frames[animation->currentFrame];

    SDL_RenderCopy(renderer, curr_frame->texture, NULL, curr_frame->bounds);

    animation->currentFrame++;
}