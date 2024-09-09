#include "../include/window_utils.h"

SDL_Window* createWindow(const char* title) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return NULL;
    }

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow(title,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          game.window_width,
                                          game.window_height,
                                          SDL_WINDOW_SHOWN);

    if (window == NULL) {
        fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    game.window = window;

    return window;
}