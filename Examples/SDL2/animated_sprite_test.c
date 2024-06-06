// gcc -I/usr/include/SDL2 -o animated_sprite_test Examples/SDL2/animated_sprite_test.c Core/Graphics/src/sprite.c Core/Graphics/src/aspect.c Core/Graphics/src/window.c Core/Graphics/src/animated_sprite.c -lSDL2 -lSDL2_image -lm && ./animated_sprite_test

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

#include "../../Core/Graphics/include/sprite.h"
#include "../../Core/Graphics/include/tilemap.h"
#include "../../Core/Graphics/include/aspect.h"
#include "../../Core/Graphics/include/animated_sprite.h"
#include "../../Core/Graphics/include/window.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32
#define NUM_SPRITES 8
#define ANIMATION_SPEED 100
#define FPS_LIMIT_RATE 16.66666666666667
#define MAX_ANIMATION 10

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Main: %s\n", SDL_GetError());
        return 1;
    }
    Aspect* aspect_window = Aspect_Init(&(SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, &(SDL_Point){0, 0}, 0.0, 0.0);
    Window* window = Window_Init("Sprite Animation", aspect_window, "Assets/Image/background1.jpg");
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return 0;
    }
    SDL_Renderer* renderer = Window_GetRenderer(window);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return 0;
    }

    AnimatedSpriteManager* manager = AnimatedSpriteManager_Init(MAX_ANIMATION);
    if (!manager) {
        SDL_Quit();
        return -1;
    }

    for (size_t i = 0; i < MAX_ANIMATION; i++) {
        Aspect* aspect_sprite = Aspect_Init(&(SDL_Rect){0, 0, 128, 128}, &(SDL_Point){0, 0}, 0.0, 0.0);
        Aspect* start = Aspect_Init(&(SDL_Rect){0 + i * 50, 0, 32, 32}, &(SDL_Point){0, 0}, 0.0, 0.0);
        Aspect* end = Aspect_Init(&(SDL_Rect){0 + i * 50, 512, 128, 128}, &(SDL_Point){0, 0}, 0.0, 0.0);

        Sprite* sprite = Sprite_Init(renderer, aspect_sprite, "Assets/Image/black_cubes.png");
        AnimatedSprite* animated_sprite = AnimatedSprite_Init(renderer, sprite, start, end, 1000 + i * 50);
        AnimatedSpriteManager_Add(manager, animated_sprite);
    }
    
    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_RenderClear(renderer);

        Sprite_RenderStatic(window->sprite, renderer);  
        AnimatedSpriteManager_Render(manager, renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(FPS_LIMIT_RATE); // Delay to limit frame rate
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window->window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}