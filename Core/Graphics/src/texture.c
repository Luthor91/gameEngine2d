#include "../include/texture.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

// Fonction d'initialisation de la texture
Texture* Texture_Init(SDL_Renderer* renderer, const char* file) {
    // Allouer de la mémoire pour la texture
    Texture* texture = (Texture*)malloc(sizeof(Texture));
    if (texture == NULL) {
        printf("Échec de l'allocation de mémoire pour la texture.\n");
        return NULL;
    }

    // Charger l'image
    SDL_Surface* surface = IMG_Load(file);
    if (surface == NULL) {
        printf("Échec de chargement de l'image %s: %s\n", file, IMG_GetError());
        free(texture);
        return NULL;
    }

    // Créer la texture à partir de la surface chargée
    texture->sdl_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture->sdl_texture == NULL) {
        printf("Échec de la création de la texture à partir de l'image %s: %s\n", file, SDL_GetError());
        SDL_FreeSurface(surface);
        free(texture);
        return NULL;
    }

    // Récupérer les dimensions de la texture
    texture->size->width = surface->w;
    texture->size->height = surface->h;

    // Libérer la surface maintenant que nous avons une texture
    SDL_FreeSurface(surface);

    return texture;
}
