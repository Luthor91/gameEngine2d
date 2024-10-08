#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../../Entities/include/entity.h"

// Structure pour le composant Sprite
typedef struct SpriteComponent {
    SDL_Texture* texture; // Texture associée au sprite
    SDL_Rect srcRect;     // Rectangle source de la texture (pour l'animation ou la découpe)
} SpriteComponent;

// Fonctions pour manipuler les composants Sprite
void addSpriteComponent(Entity entity, SpriteComponent sprite);
SpriteComponent* getSpriteComponent(Entity entity);
void removeSpriteComponent(Entity entity);

#endif // SPRITE_COMPONENT_H