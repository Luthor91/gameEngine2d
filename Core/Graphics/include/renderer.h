#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

void Renderer_Destroy(Sprite** sprites, int numRenderers);

void Renderer_Clear(Sprite** sprites, int numRenderers);

void Renderer_Sprite_Copy(Sprite** sprites, int numSprites, SDL_Renderer* renderer);

void Renderer_Present(Sprite** sprites, int numRenderers);

#endif // RENDERER_H