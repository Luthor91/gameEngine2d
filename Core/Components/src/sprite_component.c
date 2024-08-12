#include "../include/sprite_component.h"


// Fonction pour ajouter un composant Sprite à une entité
void addSpriteComponent(Entity entity, SDL_Texture* texture, SDL_Rect srcRect) {
    if (entity < MAX_ENTITIES) {
        spriteComponents[entity].texture = texture;
        spriteComponents[entity].srcRect = srcRect;
        hasSprite[entity] = true;
    }
}

// Fonction pour obtenir un composant Sprite d'une entité
SpriteComponent* getSpriteComponent(Entity entity) {
    if (entity < MAX_ENTITIES && hasSprite[entity]) {
        return &spriteComponents[entity];
    }
    return NULL;
}

// Fonction pour supprimer un composant Sprite d'une entité
void removeSpriteComponent(Entity entity) {
    if (entity < MAX_ENTITIES) {
        spriteComponents[entity].texture = NULL; // Libération éventuelle de la texture si nécessaire
        hasSprite[entity] = false;
    }
}

SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer) {
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = SDL_LoadBMP(filePath); // Vous pouvez aussi utiliser SDL_image pour d'autres formats
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    return texture;
}