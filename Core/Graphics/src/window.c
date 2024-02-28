#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/window.h"

Window* Window_Create(const char* title, int width, int height) {
    // Create the window
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        // Handle the error
        return NULL;
    }

    // Create the renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        // Handle the error
        SDL_DestroyWindow(window);
        return NULL;
    }

    // Allocate memory for the window structure
    Window* window_struct = (Window*)malloc(sizeof(Window));
    if (!window_struct) {
        // Handle the error
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return NULL;
    }

    // Set the window and renderer
    window_struct->window = window;
    window_struct->renderer = renderer;

    return window_struct;
}

void Window_Destroy(Window* window) {
    if (!window) {
        return;
    }

    SDL_DestroyTexture(window->texture);
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);

    free(window);
}

int Window_SetIcon(Window* window, const char* filename) {
    // Load the icon
    SDL_Surface* icon = SDL_LoadBMP(filename);
    if (!icon) {
        // Handle the error
        return 0;
    }

    // Set the window's icon
    SDL_SetWindowIcon(window->window, icon);

    // Free the surface
    SDL_FreeSurface(icon);

    return 1;
}

int Window_SetPosition(Window* window, int x, int y) {
    // Set the window's position on the screen
    SDL_SetWindowPosition(window->window, x, y);
    return 1;
}

int Window_SetSize(Window* window, int width, int height) {
    // Set the window's size and scale
    SDL_SetWindowSize(window->window, width, height);

    // Set the renderer's size and scale
    SDL_RenderSetLogicalSize(window->renderer, width, height);

    return 1;
}

SDL_Renderer* Window_GetRenderer(Window* window) {
    return window->renderer;
}

int Window_LoadTexture(Window* window, const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        fprintf(stderr, "IMG_Load: %s\n", IMG_GetError());
        return 0;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        fprintf(stderr, "SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
        return 0;
    }

    window->texture = texture;

    return 1;
}

void Window_Render(Window* window) {

    SDL_RenderClear(window->renderer);
    SDL_RenderCopy(window->renderer, window->texture, NULL, NULL);
    SDL_RenderPresent(window->renderer);

}