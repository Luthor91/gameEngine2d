#include "../include/render_system.h"

void renderEntities() {
    if (g_renderer == NULL) { return; }
    
    SDL_RenderClear(g_renderer);
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
        if (!hasSpriteComponent(entity)) { continue; }

        SpriteComponent* sprite = getSpriteComponent(entity);
        PositionComponent* position = getPositionComponent(entity);

        // Vérification de l'existence du TransformComponent
        TransformComponent defaultTransform = TRANSFORM_ZERO;
        TransformComponent* transform = hasTransformComponent(entity) ? getTransformComponent(entity) : &defaultTransform;

        // Définir le rectangle de destination pour le rendu
        SDL_Rect destRect = {
            .x = (int)position->x ? (int)position->x : (int)transform->x,
            .y = (int)position->y ? (int)position->y : (int)transform->y,
            .w = (int)(sprite->srcRect.w * transform->scaleX),
            .h = (int)(sprite->srcRect.h * transform->scaleY)
        };
        
        SDL_RenderCopyEx(g_renderer, sprite->texture, &sprite->srcRect, &destRect, transform->rotation, NULL, SDL_FLIP_NONE);
    }
    SDL_RenderPresent(g_renderer);
}