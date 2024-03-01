#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/window.h"
#include "../include/sprite.h"

Window* Window_Create(const char* title, int x, int y, int width, int height) {
    Window* window = (Window*)malloc(sizeof(Window));
    if (!window) {
        fprintf(stderr, "Window_Create: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Window* sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!sdl_window) {
        fprintf(stderr, "Window_Create: %s\n", IMG_GetError());
        Window_Destroy(window);
        return NULL;
    }

    window->window = sdl_window;
    window->rect.x = x;
    window->rect.y = y;
    window->rect.w = width;
    window->rect.h = height;

    return window;
}

Window* Window_Init(const char* title, int x, int y, int width, int height, const char* sprite_path, int center_x, int center_y, double scale, double angle) {
    if (!sprite_path) {
        fprintf(stderr, "Window_Init: Sprite invalide\n");
        return NULL;
    }
    
    if (scale <= 0.0) {
        fprintf(stderr, "Window_Init: Scale invalide\n");
        return NULL;
    }
    Window* window = (Window*)malloc(sizeof(Window));
    if (!window) {
        fprintf(stderr, "Window_Init: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Window* sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!sdl_window) {
        fprintf(stderr, "Window_Init: %s\n", IMG_GetError());
        Window_Destroy(window);
        return NULL;
    }

    window->window = sdl_window;

    SDL_Renderer* renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdl_window) {
        fprintf(stderr, "Window_Init: %s\n", IMG_GetError());
        Window_Destroy(window);
        return NULL;
    }

    
    window->rect.x = x;
    window->rect.y = y;
    window->rect.w = width;
    window->rect.h = height;

    Sprite* sprite = Sprite_Init(renderer, sprite_path, (SDL_Rect){x, y, width, height}, (SDL_Point){center_x, center_y}, scale, angle);

    window->sprite = sprite;

    return window;
}


void Window_Destroy(Window* window) {

    if (!window) {
        return;
    }

    SDL_DestroyTexture(window->sprite->texture);
    SDL_DestroyRenderer(window->sprite->renderer);
    SDL_DestroyWindow(window->window);

    free(window);
}

int Window_SetIcon(Window* window, const char* filename) {

    SDL_Surface* icon = SDL_LoadBMP(filename);
    if (!icon) {
        return 0;
    }

    SDL_SetWindowIcon(window->window, icon);

    SDL_FreeSurface(icon);

    return 1;
}

int Window_SetPosition(Window* window, int x, int y) {

    SDL_SetWindowPosition(window->window, x, y);
    
    return 1;
}

int Window_SetSize(Window* window, int width, int height) {

    SDL_SetWindowSize(window->window, width, height);
    SDL_RenderSetLogicalSize(window->sprite->renderer, width, height);

    return 1;
}

int Window_SyncRectWithSprite(Window* window) {

    window->rect = window->sprite->rect;
    return 1;
}

SDL_Renderer* Window_CreateRenderer(Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "Window_CreateRenderer: %s\n", IMG_GetError());
        return NULL;
    }
    return renderer;
}

SDL_Renderer* Window_GetRenderer(Window* window) {
    if (!window->sprite->renderer) {
        fprintf(stderr, "Window_GetRenderer: Invalid renderer\n");
    }
    
    return window->sprite->renderer;
}


int Window_SetSprite(Window* window, SDL_Renderer* renderer, const char* path) {
    if (!renderer) {
        fprintf(stderr, "Window_SetSprite: %s\n", IMG_GetError());
        return 0;
    }
    window->sprite = Sprite_Create(renderer, path);
    
    return 1;
}