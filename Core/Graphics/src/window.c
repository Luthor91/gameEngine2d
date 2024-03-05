#include "../include/window.h"

Window* Window_Create(const char* title, Transform* transform) {
    Window* window = (Window*)malloc(sizeof(Window));
    if (!window) {
        fprintf(stderr, "Window_Create: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Window* sdl_window = SDL_CreateWindow(title, transform->bounds->x, transform->bounds->y, transform->bounds->w, transform->bounds->h, SDL_WINDOW_SHOWN);
    if (!sdl_window) {
        fprintf(stderr, "Window_Create: %s\n", IMG_GetError());
        free(window);
        return NULL;
    }

    window->window = sdl_window;
    window->transform = transform;

    return window;
}

Window* Window_Init(const char* title, Transform* transform, const char* sprite_path) {

    if (!sprite_path) {
        fprintf(stderr, "Window_Init: Sprite invalide\n");
        return NULL;
    }
    
    if (transform->scale <= 0.0) {
        transform->scale = 1.0;
    }

    Window* window = (Window*)malloc(sizeof(Window));
    if (!window) {
        fprintf(stderr, "Window_Init: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Window* sdl_window = SDL_CreateWindow(title, transform->bounds->x, transform->bounds->y, transform->bounds->w, transform->bounds->h, SDL_WINDOW_SHOWN);
    if (!sdl_window) {
        fprintf(stderr, "Window_Init: %s\n", IMG_GetError());
        free(window);
        return NULL;
    }

    window->window = sdl_window;
    window->transform = transform;

    SDL_Renderer* renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "Window_Init: %s\n", IMG_GetError());
        free(window);
        return NULL;
    }
    window->renderer = renderer;
    
    window->sprite = Sprite_Init(window->renderer, window->transform, sprite_path);
    if (!window->sprite) {
        fprintf(stderr, "Window_Init: Erreur création du sprite\n");
        free(window);
        return NULL;
    }
    
    return window;
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

SDL_Renderer* Window_CreateRenderer(Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "Window_CreateRenderer: %s\n", IMG_GetError());
        return NULL;
    }
    return renderer;
}

SDL_Renderer* Window_GetRenderer(Window* window) {
    if (!window->renderer) {
        fprintf(stderr, "Window_GetRenderer: Invalid renderer\n");
    }
    
    return window->renderer;
}

int Window_SetSprite(Window* window, const SDL_Renderer* renderer, const char* path) {
    if (!renderer) {
        fprintf(stderr, "Window_SetSprite: %s\n", IMG_GetError());
        return 0;
    }

    window->sprite = Sprite_Init(window->renderer, window->transform, path);
    
    return 1;
}