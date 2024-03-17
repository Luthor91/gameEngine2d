// gcc -I/usr/include/SDL2 -o animation_test Examples/SDL2/animation_test.c Core/Graphics/src/sprite.c Core/Graphics/src/tilemap.c Core/Graphics/src/transform.c Core/Graphics/src/window.c -lSDL2 -lSDL2_image -lm && ./animation_test

#include "../include/animation.h"

Animation* Animation_Init(SDL_Renderer* renderer, Sprite* sprite, int tile_width, int tile_height, int max_sprite, int speed) {

    if (!sprite || !sprite->texture) {
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

    animation->lastFrameTime = SDL_GetTicks();
    animation->currentFrame = 0;
    animation->max_sprite = max_sprite;
    animation->speed = speed;

    Frame** frames = (Frame**)malloc(num_cols * num_rows * sizeof(Frame*));
    int frame_index = 0;

    // Boucle de création de frames
    for (int y = 0; y < num_cols; y++) {
        for (int x = 0; x < num_rows; x++) {
            int frame_index = y * num_cols + x; // Calcul de l'index de frame
            
            if (frame_index >= max_sprite) {
                break;
            }
            printf("index:%d; col:%d; row:%d\n", frame_index, y, x);
            Frame* frame = (Frame*)malloc(sizeof(Frame));
            if (!frame) {
                printf("Animation_Init: Error init frame\n");
                free(frame);
                return NULL;
            }
             
            frame->origin = (SDL_Rect*)malloc(sizeof(SDL_Rect));
            if (!frame->origin) {
                printf("Animation_Init: Erreur lors de l'allocation de mémoire pour les limites du frame\n");
                free(frame->origin);
                return NULL;
            }
            frame->origin->x = x * tile_width;
            frame->origin->y = y * tile_height;
            frame->origin->w = tile_width;
            frame->origin->h = tile_height;

            frame->target = (SDL_Rect*)malloc(sizeof(SDL_Rect));
            if (!frame->target) {
                printf("Animation_Init: Erreur lors de l'allocation de mémoire pour la cible du rendu du frame\n");
                free(frame->target);
                return NULL;
            }
            frame->target->x = 0;
            frame->target->y = 0;
            frame->target->w = tile_width;
            frame->target->h = tile_height;

            SDL_Texture* frame_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, tile_width, tile_height);
            if (!frame_texture){
                fprintf(stderr, "Animation_Init: Erreur création sous-texture:\n\t %s\n", SDL_GetError());
            }
            SDL_SetTextureBlendMode(frame_texture, SDL_BLENDMODE_NONE);
            SDL_SetRenderTarget(renderer, frame_texture); // Active la texture cible
            SDL_RenderCopy(renderer, sprite->texture, frame->origin, frame->target);
            SDL_SetRenderTarget(renderer, NULL); // Désactive la texture cible
            SDL_SetTextureBlendMode(frame_texture, SDL_BLENDMODE_BLEND);   

            frame->texture = frame_texture;
            frame->id = frame_index;
            frames[frame_index] = frame;
        }
    }
    animation->render_semaphore = SDL_CreateSemaphore(0);
    if (animation->render_semaphore == NULL) {
        printf("Animation_Init: Failed to create semaphore: \n\t%s\n", SDL_GetError());
        free(animation);
        return NULL;
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
    // Obtient la frame actuelle
    Frame* curr_frame = animation->frames[animation->currentFrame];

    // Rend la frame actuelle
    SDL_RenderCopy(renderer, curr_frame->texture, NULL, curr_frame->target);

    // Attend le délai avant de passer à la frame suivante
    int current_time = SDL_GetTicks();
    int elapsed_time = current_time - animation->lastFrameTime;
    if (elapsed_time < animation->speed) {
        SDL_Delay(animation->speed - elapsed_time);
    }
    animation->lastFrameTime = SDL_GetTicks();
}

int Animation_Render_Thread(void* data) {
    Animation_Wrapper* animation_wrapper = (Animation_Wrapper*)data;
    Animation* animation = animation_wrapper->animation;
    SDL_Renderer* renderer = animation_wrapper->renderer;
    int repeat = animation_wrapper->repeat;
    SDL_cond* render_cond = animation_wrapper->render_cond; // Récupérer la variable de condition

    int i = 0;
    while (i < repeat) {   
        Animation_Render(animation, renderer);

        // Signal au thread principal qu'une nouvelle frame est prête
        if (SDL_CondSignal(render_cond) != 0) {
            printf("Animation_Render_Thread: error signaling render condition: %s\n", SDL_GetError());
            return 0;
        }

        i++;
        printf("repeat : %d\n", i);
    }

    return 1;
}
