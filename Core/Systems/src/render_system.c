#include "../include/render_system.h"

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

    game.renderer = renderer;

    return renderer;
}

// Fonction pour rendre les entités et les particules
void renderEntities() {
    if (game.renderer == NULL) { return; }
            
    SDL_RenderClear(game.renderer);

    // Rendu des entités
    for (Entity entity = 0; entity < getEntityCount(); ++entity) {
        if (!hasSpriteComponent(entity) || !isEntityEnabled(entity)) { continue; }

        SpriteComponent* sprite = getSpriteComponent(entity);
        PositionComponent* position = getPositionComponent(entity);

        // Vérification de l'existence du TransformComponent
        TransformComponent defaultTransform = TRANSFORM_ZERO;
        TransformComponent* transform = hasTransformComponent(entity) ? getTransformComponent(entity) : &defaultTransform;

        // Définir le rectangle de destination pour le rendu
        SDL_Rect destRect = {
            .x = (int)(position->x + transform->x),
            .y = (int)(position->y + transform->y),
            .w = (int)(sprite->srcRect.w * transform->scaleX),
            .h = (int)(sprite->srcRect.h * transform->scaleY)
        };
        SDL_SetTextureBlendMode(sprite->texture, SDL_BLENDMODE_BLEND);
        SDL_RenderCopyEx(game.renderer, sprite->texture, &sprite->srcRect, &destRect, transform->rotation, NULL, SDL_FLIP_NONE);
    }

    // Rendu des particules
    ParticleEmitter* emitters = getEmitters();
    for (int i = 0; i < getActiveEmitterCount(); ++i) {
        ParticleEmitter* emitter = &emitters[i];
        if (emitter->active == 0) continue;
        
        for (int j = 0; j < emitter->particleCount; ++j) {
            Particle* particle = &emitter->particles[j];
            if (particle->active == 0) continue;
            // Définir le rectangle de destination pour le rendu des particules
            SDL_Rect particleRect = {
                .x = (int)particle->position.x,
                .y = (int)particle->position.y,
                .w = (int)(particle->srcRect.w * particle->size),
                .h = (int)(particle->srcRect.h * particle->size)
            };

            SDL_RenderCopy(game.renderer, particle->texture, &particle->srcRect, &particleRect);
        }
    }

    SDL_RenderPresent(game.renderer);
}

void renderEntitiesWithHitboxes() {
    if (game.renderer == NULL) { return; }
    
    SDL_RenderClear(game.renderer); // Effacer le contenu précédent

    // Parcourir toutes les entités
    for (Entity entity = 0; entity < getEntityCount(); ++entity) {
        if (!isEntityEnabled(entity)) { continue; }

        // Rendu de l'entité si elle a un composant Sprite
        if (hasSpriteComponent(entity)) {
            SpriteComponent* sprite = getSpriteComponent(entity);
            PositionComponent* position = getPositionComponent(entity);

            TransformComponent defaultTransform = TRANSFORM_ZERO;
            TransformComponent* transform = hasTransformComponent(entity) ? getTransformComponent(entity) : &defaultTransform;

            SDL_Rect destRect = {
                .x = (int)(position->x + transform->x),
                .y = (int)(position->y + transform->y),
                .w = (int)(sprite->srcRect.w * transform->scaleX),
                .h = (int)(sprite->srcRect.h * transform->scaleY)
            };
            SDL_SetTextureBlendMode(sprite->texture, SDL_BLENDMODE_BLEND);
            SDL_RenderCopyEx(game.renderer, sprite->texture, &sprite->srcRect, &destRect, transform->rotation, NULL, SDL_FLIP_NONE);
        }

        // Rendu de la hitbox si elle est disponible
        if (hasHitboxComponent(entity)) {
            HitboxComponent* hitbox = getHitboxComponent(entity);
            PositionComponent* position = getPositionComponent(entity);

            SDL_Rect hitboxRect = {
                .x = (int)(position->x + hitbox->x),
                .y = (int)(position->y + hitbox->y),
                .w = (int)hitbox->width,
                .h = (int)hitbox->height
            };
            
            // Définir la couleur des lignes des hitboxes
            if (hitbox->is_active) {
                SDL_SetRenderDrawColor(game.renderer, 0, 255, 0, 255); // Vert pour active
            } else {
                SDL_SetRenderDrawColor(game.renderer, 255, 0, 0, 255); // Rouge pour inactive
            }

            // Dessiner uniquement les bordures de la hitbox
            SDL_RenderDrawRect(game.renderer, &hitboxRect);
        }
    }

    // Rendu des particules
    ParticleEmitter* emitters = getEmitters();
    for (int i = 0; i < getActiveEmitterCount(); ++i) {
        ParticleEmitter* emitter = &emitters[i];
        if (emitter->active == 0) continue;

        for (int j = 0; j < emitter->particleCount; ++j) {
            Particle* particle = &emitter->particles[j];
            if (particle->active == 0) continue;

            SDL_Rect particleRect = {
                .x = (int)particle->position.x,
                .y = (int)particle->position.y,
                .w = (int)(particle->srcRect.w * particle->size),
                .h = (int)(particle->srcRect.h * particle->size)
            };

            SDL_RenderCopy(game.renderer, particle->texture, &particle->srcRect, &particleRect);
        }
    }

    SDL_RenderPresent(game.renderer); // Présenter le rendu final
}
