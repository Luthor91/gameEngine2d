#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>

void Renderer_Destroy(SDL_Renderer** renderers, int numRenderers);

void Renderer_Clear(SDL_Renderer** renderers, int numRenderers);

void Renderer_Sprite_Copy(Sprite** sprites, int numSprites);

void Renderer_Present(SDL_Renderer** renderers, int numRenderers);

#endif // RENDERER_H