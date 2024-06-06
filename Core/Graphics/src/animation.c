// gcc -I/usr/include/SDL2 -o animation_test Examples/SDL2/animation_test.c Core/Graphics/src/sprite.c Core/Graphics/src/tilemap.c Core/Graphics/src/aspect.c Core/Graphics/src/window.c Core/Graphics/src/frame.c -lSDL2 -lSDL2_image -lm && ./animation_test

#include "../include/animation.h"

Animation* Animation_Init(SDL_Renderer* renderer, Sprite* sprite, SDL_Rect* target, int tile_width, int tile_height, int max_frame, int speed) {
    if (!sprite || !sprite->texture) {
        printf("Animation_Init: Erreur lors de la création de la texture\n");
        return NULL;
    }

    int num_cols = sprite->aspect->bounds->w / tile_width;
    int num_rows = sprite->aspect->bounds->h / tile_height;

    Animation* animation = (Animation*)malloc(sizeof(Animation));
    if (!animation) {
        printf("Animation_Init: Erreur lors de l'allocation de mémoire pour l'animation\n");
        SDL_DestroyTexture(sprite->texture);
        return NULL;
    }

    animation->lastFrameTime = SDL_GetTicks();
    animation->currentFrame = 0;
    animation->max_frame = max_frame;
    animation->speed = speed;

    Frame** frames = (Frame**)malloc(num_cols * num_rows * sizeof(Frame*));
    int frame_index = 0;

    for (int y = 0; y < num_cols; y++) {
        for (int x = 0; x < num_rows; x++) {
            frame_index = y * num_cols + x; // Calcul de l'index de frame
            
            if (frame_index >= max_frame) {
                break;
            }

            SDL_Rect origin = (SDL_Rect) { x * tile_width, y * tile_height, tile_width, tile_height};

            SDL_Texture* frame_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, target->w, target->h);
            if (!frame_texture){
                fprintf(stderr, "Animation_Init: Erreur création sous-texture:\n\t %s\n", SDL_GetError());
                free(target);
                return NULL;
            }

            Frame* frame = Frame_Init(&origin, target, frame_texture, frame_index);

            SDL_SetTextureBlendMode(frame_texture, SDL_BLENDMODE_NONE);
            SDL_SetRenderTarget(renderer, frame_texture); // Active la texture cible
            SDL_RenderCopy(renderer, sprite->texture, &origin, target);
            SDL_SetRenderTarget(renderer, NULL); // Désactive la texture cible
            SDL_SetTextureBlendMode(frame_texture, SDL_BLENDMODE_BLEND);   

            frames[frame_index] = frame;

        }
    }
    animation->frames = frames;

    return animation;
}

void Animation_Delay(Animation* animation) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - animation->lastFrameTime > animation->speed) {
        animation->currentFrame = (animation->currentFrame + 1) % animation->max_frame;
        animation->lastFrameTime = currentTime;
    }
}

void Animation_Render(Animation* animation, SDL_Renderer* renderer) {
    if (animation->currentFrame >= animation->max_frame) {
        animation->currentFrame = 0;
        return;
    }
    Frame* curr_frame = animation->frames[animation->currentFrame];
    SDL_RenderCopy(renderer, curr_frame->texture, NULL, curr_frame->target);
    Frame_Render_Debug(curr_frame, renderer);

    int current_time = SDL_GetTicks();
    int elapsed_time = current_time - animation->lastFrameTime;
    
    if (elapsed_time < animation->speed) {
        SDL_Delay(animation->speed - elapsed_time);
    }

    animation->currentFrame++;
    animation->lastFrameTime = SDL_GetTicks();

    // Debugging information
    printf("Frame %d: target: (%d, %d, %d, %d)\n",
        animation->currentFrame,
        curr_frame->target->x, curr_frame->target->y, curr_frame->target->w, curr_frame->target->h
    );

}