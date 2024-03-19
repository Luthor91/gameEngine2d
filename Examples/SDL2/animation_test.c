// gcc -I/usr/include/SDL2 -o animation_test Examples/SDL2/animation_test.c Core/Graphics/src/sprite.c Core/Graphics/src/tilemap.c Core/Graphics/src/transform.c Core/Graphics/src/window.c Core/Graphics/src/animation.c -lSDL2 -lSDL2_image -lm && ./animation_test


#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

#include "../../Core/Graphics/include/sprite.h"
#include "../../Core/Graphics/include/tilemap.h"
#include "../../Core/Graphics/include/transform.h"
#include "../../Core/Graphics/include/animation.h"
#include "../../Core/Graphics/include/window.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32
#define NUM_SPRITES 8
#define ANIMATION_SPEED 100

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Main: %s\n", SDL_GetError());
        return 1;
    }
    Transform* transform_window = Transform_Init(&(SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, &(SDL_Point){0, 0}, 0.0, 0.0);
    Window* window = Window_Init("Sprite Animation", transform_window, "Assets/Image/background1.jpg");
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return 0;
    }
    SDL_Renderer* renderer = Window_GetRenderer(window);
    
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return 0;
    }

    Transform* transform_sprite = Transform_Init(&(SDL_Rect){0, 0, 128, 128}, &(SDL_Point){0, 0}, 0.0, 0.0);
    Sprite* sprite = Sprite_Init(renderer, transform_sprite, "Assets/Image/arrows.png");
    /* Init via tilemap
    Tilemap* tilemap = Tilemap_Init(sprite, SPRITE_WIDTH, SPRITE_HEIGHT);
    Animation* animation = Animation_Init(tilemap, 8, 100);
    */
    Animation* animation = Animation_Init(renderer, sprite, 32, 32, 8, 100);

    SDL_Rect** bounds = (SDL_Rect**)malloc( animation->max_sprite * sizeof(SDL_Rect*));
    for(int i = 0; i < animation->max_sprite; i++) {
        bounds[i] = &(SDL_Rect){32, 32, 32, 32};

    }

    SDL_Event event;
    int quit = 0;

    SDL_cond* condition = SDL_CreateCond();
    if (!condition) {
        printf("Main: Failed to create render condition: %s\n", SDL_GetError());
        return 1;
    }
    SDL_mutex* mutex = SDL_CreateMutex();
    if (!mutex) {
        printf("Main: Failed to create mutex: %s\n", SDL_GetError());
        return 1;
    }

    Animation_Wrapper animation_wrapper = {animation, renderer, 100, condition, mutex};
    SDL_Thread* threadID = SDL_CreateThread(Animation_Render_Thread, "Animation Render Thread", &animation_wrapper);
    if (!threadID) {
        printf("Main: Failed to create thread: \n\t%s\n", SDL_GetError());
        free(threadID);
        return 1;
    }

    SDL_DetachThread(threadID);

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_RenderClear(renderer);
        Sprite_RenderStatic(window->sprite, renderer);  

        // Attendre que la variable de condition soit signalée
        SDL_CondWait(animation_wrapper.condition, animation_wrapper.mutex);

        SDL_RenderCopy(renderer, animation->frames[animation->currentFrame]->texture, NULL, animation->frames[animation->currentFrame]->target);
        SDL_RenderPresent(renderer);
        
        SDL_Delay(10); // Delay to limit frame rate
    }

    //SDL_DestroyTexture(tilemap->texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window->window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
