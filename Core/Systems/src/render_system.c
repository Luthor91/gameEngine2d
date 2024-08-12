#include "../include/render_system.h"

void renderEntities(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
        SpriteComponent* sprite = getSpriteComponent(entity);
        TransformComponent* transform = getTransformComponent(entity);
        
        if (sprite && sprite->texture && transform) {
            SDL_Rect destRect = {
                (int)transform->x,
                (int)transform->y,
                (int)(sprite->srcRect.w * transform->scaleX),
                (int)(sprite->srcRect.h * transform->scaleY)
            };
            
            SDL_RenderCopyEx(renderer, sprite->texture, &sprite->srcRect, &destRect, transform->rotation, NULL, SDL_FLIP_NONE);
        }
    }
    SDL_RenderPresent(renderer);
}
