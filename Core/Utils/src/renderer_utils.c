#include "../include/renderer_utils.h"

SDL_Renderer* createRenderer(SDL_Window* window) {
    if (window == NULL) {
        fprintf(stderr, "La fenêtre doit être non nulle pour créer un renderer.\n");
        return NULL;
    }

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
        fprintf(stderr, "Erreur de création du renderer: %s\n", SDL_GetError());
        return NULL;
    }

    return renderer;
}
