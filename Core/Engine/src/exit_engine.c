#include "../include/exit_engine.h"

void Free_entity_attributes() {
    // Libération de la mémoire allouée pour chaque tableau
    free(entityStates);
    free(hasSprite);
    free(hasPosition);
    free(hasVelocity);
    free(hasInput);
    free(hasTransform);
    free(hasAnimation);
    free(hasHitbox);
    free(hasSize);
    free(hasTags);
    free(hasDatas);
}

void Exit_All() {
    Free_entity_attributes();
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}