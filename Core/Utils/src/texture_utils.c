#include "../include/texture_utils.h"

SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer) {
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = IMG_Load(filePath);
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    
    return texture;
}

// Fonction pour créer une texture de couleur unie
SDL_Texture* loadColor(SDL_Renderer* renderer, SDL_Color color, int width, int height) {
    // Créer une surface avec la couleur spécifiée
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    if (!surface) {
        printf("Erreur lors de la création de la surface : %s\n", SDL_GetError());
        return NULL;
    }

    // Remplir la surface avec la couleur spécifiée
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));

    // Créer une texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }

    // Libérer la surface car elle n'est plus nécessaire
    SDL_FreeSurface(surface);

    return texture;
}