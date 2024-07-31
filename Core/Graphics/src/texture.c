#include "../include/texture.h"

Texture* Texture_Init(SDL_Renderer* renderer, char* file) {

    if (renderer == NULL) {
        renderer = SDL_Renderer_Current();
    }

    if (file == NULL) {
        fprintf(stderr, "Texture_Init: Sprite path is invalid, default value used\n");
        file = "Assets/Default/DefaultObject.png";
    }

    // Allouer de la mémoire pour la texture
    Texture* texture = (Texture*)malloc(sizeof(Texture));
    if (texture == NULL) {
        printf("Texture_Init : Échec de l'allocation de mémoire pour la texture.\n");
        return NULL;
    }
    
    // Charger l'image
    SDL_Surface* surface = IMG_Load(file);
    if (surface == NULL) {
        printf("Texture_Init : Échec de chargement de l'image %s: %s\n", file, IMG_GetError());
        free(texture);
        return NULL;
    }

    // Créer la texture à partir de la surface chargée
    texture->sdl_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture->sdl_texture == NULL) {
        printf("Texture_Init : Échec de la création de la texture à partir de l'image %s: %s\n", file, SDL_GetError());
        SDL_FreeSurface(surface);
        free(texture);
        return NULL;
    }

    // Récupérer les dimensions de la texture
    texture->size = Size2D_Init(surface->w, surface->h);

    // Libérer la surface maintenant que nous avons une texture
    SDL_FreeSurface(surface);

    return texture;
}

Texture* Texture_Init_Color(SDL_Renderer* renderer, Color* color, Size2D* size) {
    if (renderer == NULL) {
        renderer = SDL_Renderer_Current();
    }

    if (color == NULL) {
        color = &COLOR_WHITE;
    }

    if (size == NULL) {
        size = Size2D_Init(DEFAULT_SIZE2D_WIDTH, DEFAULT_SIZE2D_HEIGHT);
    }

    // Allouer de la mémoire pour la texture
    Texture* texture = (Texture*)malloc(sizeof(Texture));
    if (texture == NULL) {
        printf("Texture_Init_Color : Échec de l'allocation de mémoire pour la texture.\n");
        return NULL;
    }

    // Créer la texture SDL
    texture->sdl_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size->width, size->height);
    if (texture->sdl_texture == NULL) {
        printf("Texture_Init_Color : Échec de la création de la texture: %s\n", SDL_GetError());
        free(texture);
        return NULL;
    }
    
    // Sauvegarder la cible de rendu actuelle
    SDL_Texture* previous_target = SDL_GetRenderTarget(renderer);

    // Définir la texture comme cible de rendu
    SDL_SetRenderTarget(renderer, texture->sdl_texture);

    // Remplir la texture avec la couleur spécifiée
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_RenderClear(renderer);

    // Réinitialiser la cible de rendu précédente
    SDL_SetRenderTarget(renderer, previous_target);

    // Définir la taille de la texture
    texture->size = size;

    return texture;
}


Texture* Texture_Crop(Texture* original, SDL_Renderer* renderer, Point2D* pos, Size2D* size) {
    // Vérifiez les paramètres d'entrée
    if (!original || !renderer || !pos || !size) {
        printf("Texture_Crop: Paramètres invalides.\n");
        return NULL;
    }

    // Définir le rectangle source
    SDL_Rect src_rect = { pos->x, pos->y, size->width, size->height };

    // Créer une nouvelle texture cible
    SDL_Texture* new_sdl_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size->width, size->height);
    if (!new_sdl_texture) {
        printf("Texture_Crop: Erreur de création de texture SDL: %s\n", SDL_GetError());
        return NULL;
    }

    // Activer le mode de mélange pour la nouvelle texture
    if (SDL_SetTextureBlendMode(new_sdl_texture, SDL_BLENDMODE_BLEND) != 0) {
        printf("Texture_Crop: Erreur lors de la définition du mode de mélange: %s\n", SDL_GetError());
        SDL_DestroyTexture(new_sdl_texture);
        return NULL;
    }

    // Sauvegarder la cible de rendu actuelle
    SDL_Texture* current_target = SDL_GetRenderTarget(renderer);

    // Définir la nouvelle texture comme cible de rendu
    if (SDL_SetRenderTarget(renderer, new_sdl_texture) != 0) {
        printf("Texture_Crop: Erreur lors de la définition de la texture cible: %s\n", SDL_GetError());
        SDL_DestroyTexture(new_sdl_texture);
        return NULL;
    }

    // Effacer la nouvelle texture (facultatif, utile si vous voulez un fond transparent)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // Copier la texture source vers la nouvelle texture
    if (SDL_RenderCopy(renderer, original->sdl_texture, &src_rect, NULL) != 0) {
        printf("Texture_Crop: Erreur lors de la copie de la texture: %s\n", SDL_GetError());
        SDL_SetRenderTarget(renderer, current_target); // Restaurer la cible de rendu
        SDL_DestroyTexture(new_sdl_texture);
        return NULL;
    }

    // Restaurer la cible de rendu précédente
    SDL_SetRenderTarget(renderer, current_target);

    // Allouer et initialiser la nouvelle texture
    Texture* new_texture = (Texture*)malloc(sizeof(Texture));
    if (!new_texture) {
        printf("Texture_Crop: Erreur d'allocation de mémoire pour la nouvelle texture.\n");
        SDL_DestroyTexture(new_sdl_texture);
        return NULL;
    }
    new_texture->sdl_texture = new_sdl_texture;
    new_texture->size = (Size2D*)malloc(sizeof(Size2D));
    if (!new_texture->size) {
        printf("Texture_Crop: Erreur d'allocation de mémoire pour la taille de la nouvelle texture.\n");
        SDL_DestroyTexture(new_sdl_texture);
        free(new_texture);
        return NULL;
    }
    new_texture->size->width = size->width;
    new_texture->size->height = size->height;

    return new_texture;
}
