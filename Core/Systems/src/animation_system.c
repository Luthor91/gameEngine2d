#include "../include/animation_system.h"
#include <SDL2/SDL.h>

// Fonction pour obtenir la largeur de la texture à partir du SpriteComponent
int getTextureWidth(SDL_Texture* texture) {
    int width = 0;
    SDL_QueryTexture(texture, NULL, NULL, &width, NULL);
    return width;
}

// Fonction pour obtenir la hauteur de la texture à partir du SpriteComponent
int getTextureHeight(SDL_Texture* texture) {
    int height = 0;
    SDL_QueryTexture(texture, NULL, NULL, NULL, &height);
    return height;
}

void updateAnimations() {
    Uint32 currentTime = SDL_GetTicks();

    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
        AnimationComponent* animation = getAnimationComponent(entity);
        SpriteComponent* sprite = getSpriteComponent(entity);

        if (animation && sprite) {
            if (currentTime > animation->lastFrameTime + animation->frameDuration) {
                animation->currentFrame = (animation->currentFrame + 1) % animation->totalFrames;
                animation->lastFrameTime = currentTime;

                // Mettre à jour le srcRect du SpriteComponent pour correspondre à la nouvelle frame
                int frameWidth = sprite->srcRect.w;
                int frameHeight = sprite->srcRect.h;
                int textureWidth = getTextureWidth(sprite->texture);
                int textureHeight = getTextureHeight(sprite->texture);

                // Assumer que les frames sont alignées horizontalement
                sprite->srcRect.x = (animation->currentFrame % (textureWidth / frameWidth)) * frameWidth;
                sprite->srcRect.y = (animation->currentFrame / (textureWidth / frameWidth)) * frameHeight;

                // Vérifiez si le rectangle source est valide
                if (sprite->srcRect.x < 0 || sprite->srcRect.y < 0 || sprite->srcRect.x >= textureWidth || sprite->srcRect.y >= textureHeight) {
                    printf("Warning: srcRect is out of bounds. x: %d, y: %d\n", sprite->srcRect.x, sprite->srcRect.y);
                }
            }
        }
    }
}

