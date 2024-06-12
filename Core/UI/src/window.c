#include "../include/window.h"

Window* Window_Init(const char* title, Transform* transform, const char* background_path) {
    if (!background_path) {
        fprintf(stderr, "Window_Init: Sprite path is invalid\n");
        return NULL;
    }

    if (transform->scale <= 0.0) {
        transform->scale = 1.0;
    }
    Window* window = (Window*)malloc(sizeof(Window));
    if (!window) {
        fprintf(stderr, "Window_Init: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Window* sdl_window = SDL_CreateWindow(
        title,
        (int)transform->position->x,
        (int)transform->position->y,
        (int)(transform->size->width * transform->scale),
        (int)(transform->size->height * transform->scale),
        SDL_WINDOW_SHOWN
    );
    if (!sdl_window) {
        fprintf(stderr, "Window_Init: %s\n", SDL_GetError());
        free(window);
        return NULL;
    }

    window->sdl_window = sdl_window;
    window->transform = transform;

    SDL_Renderer* renderer = SDL_CreateRenderer(window->sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "Window_Init: %s\n", SDL_GetError());
        SDL_DestroyWindow(window->sdl_window);
        free(window);
        return NULL;
    }

    window->renderer = renderer;

    window->texture = Texture_Init(window->renderer, background_path);
    if (!window->texture) {
        fprintf(stderr, "Window_Init: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window->sdl_window);
        free(window);
        return NULL;
    }

    window->texture = Texture_Init(window->renderer, background_path);
    window->texture->size = transform->size;

    return window;
}

int Window_SetIcon(Window* window, const char* filename) {
    SDL_Surface* icon = SDL_LoadBMP(filename);
    if (!icon) {
        return 0;
    }

    SDL_SetWindowIcon(window->sdl_window, icon);
    SDL_FreeSurface(icon);

    return 1;
}

void Window_Destroy(Window* window) {
    if (window) {
        if (window->texture) {
            SDL_DestroyTexture(window->texture->sdl_texture);
            free(window->texture);
        }
        if (window->renderer) {
            SDL_DestroyRenderer(window->renderer);
        }
        if (window->sdl_window) {
            SDL_DestroyWindow(window->sdl_window);
        }
        free(window);
    }
}
