#include "../include/sprite_component.h"

static SpriteComponent spriteComponents[MAX_ENTITIES];

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