#include "../include/sdl_renderer.h"
#include <stdlib.h>
#include <stdio.h>

// Définition des variables globales dans le fichier source
static SDL_Renderer** windows_renderers = NULL; // Initialisation du tableau de renderers à NULL
static int sdl_renderer_count = 0;              // Initialisation du compteur de renderers à 0
static int current_sdl_renderer = 0;            // Initialisation de l'index du renderer courant à 0

void SDL_Renderer_Add(SDL_Renderer* renderer) {
    // Si c'est la première fois que nous ajoutons un renderer, initialiser le tableau
    if (windows_renderers == NULL) {
        windows_renderers = (SDL_Renderer**)malloc(MAX_RENDERER_CAPACITY * sizeof(SDL_Renderer*));
        if (windows_renderers == NULL) {
            fprintf(stderr, "SDL_Renderer_Add: Memory allocation failed for windows_renderers.\n");
            return;
        }
    }

    // Si le tableau est plein, augmenter la capacité
    if (sdl_renderer_count >= MAX_RENDERER_CAPACITY) {
        fprintf(stderr, "SDL_Renderer_Add: too many SDL_Renderers.\n");
        return;
    }
    // Ajouter le renderer au tableau
    windows_renderers[sdl_renderer_count++] = renderer;
}

SDL_Renderer* SDL_Renderer_Get(int index) {
    if (index >= sdl_renderer_count || index < 0) {
        fprintf(stderr, "SDL_Renderer_Get: index out of bounds.\n");
        return NULL;
    }  
    return windows_renderers[index];
}

SDL_Renderer* SDL_Renderer_Current() {
    return windows_renderers[current_sdl_renderer];
}
