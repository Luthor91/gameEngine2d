// gcc -I/usr/include/SDL2 -o animated_timer_test Examples/SDL2/animated_timer_test.c Core/Events/src/timer_manager.c Core/Graphics/src/transform.c Core/Graphics/src/window.c Core/Graphics/src/frame.c Core/Graphics/src/sprite.c Core/Graphics/src/spritesheet.c Core/Graphics/src/animated_spritesheet.c -lSDL2 -lSDL2_image -lm && ./animated_timer_test


#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

#include "../../Core/Graphics/include/sprite.h"
#include "../../Core/Graphics/include/transform.h"
#include "../../Core/Graphics/include/sprite.h"
#include "../../Core/Graphics/include/spritesheet.h"
#include "../../Core/Graphics/include/animated_spritesheet.h"
#include "../../Core/Graphics/include/window.h"
#include "../../Core/Events/include/timer_manager.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32
#define NUM_SPRITES 8
#define ANIMATION_SPEED 100

void MyCallbackFunction(void* data) {
    printf("Timer expired!\n\tData : %c\n", data);
}

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
    SpriteSheet* spritesheet = SpriteSheet_Init(renderer, sprite, 32, 32, 8);
    AnimatedSpriteSheet* animated_sprite = AnimatedSpriteSheet_Init(renderer, spritesheet, &(SDL_Rect){0, 0, 32, 32}, &(SDL_Rect){512, 512, 32, 32}, 2500, 1);

    SDL_Event event;
    int quit = 0;

    TimerManager manager;
    TimerManager_Init(&manager);
    
    TimerManager_AddTimer(&manager, 1, 2000, MyCallbackFunction, (void*)'A', 0);
    TimerManager_AddTimer(&manager, 2, 1500, MyCallbackFunction, (void*)'B', 1);
    
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_RenderClear(renderer);
        Sprite_RenderStatic(window->sprite, renderer); 
        AnimatedSpriteSheet_Render(animated_sprite, renderer);
        TimerManager_Update(&manager);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60); // Delay to limit frame rate
    }

    //SDL_DestroyTexture(tilemap->texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window->window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}