#include <SDL2/SDL.h>
#include "../include/sprite.h"

// Détruit un tableau de renderers
void Renderer_Destroy(Sprite** sprites, int numRenderers) {
    for (int i = 0; i < numRenderers; i++) {
        SDL_DestroyRenderer(sprites[i]);
        free(sprites[i]);
    }
    free(sprites);
}

// Efface tous les renderers d'un tableau
void Renderer_Clear(Sprite** sprites, int numRenderers) {
    for (int i = 0; i < numRenderers; i++) {
        SDL_RenderClear(sprites[i]->renderer);
    }
}

// Copie une texture sur chaque renderer d'un tableau
void Renderer_Sprite_Copy(Sprite** sprites, int numSprites) {
    for (int i = 0; i < numSprites; i++) {
        SDL_RenderCopy(sprites[i]->renderer, sprites[i]->texture, &sprites[i]->rect, NULL);
    }
}

// Présente chaque renderer d'un tableau
void Renderer_Present(Sprite** sprites, int numRenderers) {
    for (int i = 0; i < numRenderers; i++) {
        SDL_RenderPresent(sprites[i]->renderer);
    }
}