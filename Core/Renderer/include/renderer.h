#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include "../../Animation/include/dynamic_animation.h"
#include "../../Animation/include/static_animation.h"
#include "../../Animation/include/animation.h"
#include "../../Graphics/include/sprite.h"

#include "../../Graphics/include/color.h"

#include "../../Spatial/include/point2d.h"
#include "../../Spatial/include/size2d.h"
#include "../../Font/include/label.h"
#include "../../Font/include/font.h"

#include "../../UI/include/window.h"

typedef struct Renderer {
    void (*renderFunction)(struct Renderer*, SDL_Renderer*); 
    void* object; // Pointeur vers l'objet spécifique
    int z_index;
} Renderer;

typedef struct RendererManager {
    Renderer** renderers; // Pointeur vers la fonction de rendu
    SDL_Renderer* sdl_renderer;
    int max_renderers;
    int current_renderer_count;
} RendererManager;

RendererManager* RendererManager_Init(SDL_Renderer* sdl_renderer, int max_renderers);
Renderer* Renderer_Init(void* renderFunction, void* object, int z_index);
void RendererManager_Add(RendererManager* manager, Renderer* renderer);
void RendererManager_Sort(RendererManager* manager);
void RendererManager_Render(RendererManager* manager);

void Renderer_DynamicAnimation(Renderer* renderer, SDL_Renderer* sdl_renderer);
void Renderer_StaticAnimation(Renderer* renderer, SDL_Renderer* sdl_renderer);
void Renderer_Sprite(Renderer* renderer, SDL_Renderer* sdl_renderer);
void Renderer_Label(Renderer* renderer, SDL_Renderer* sdl_renderer);
void Renderer_Window(Renderer* renderer, SDL_Renderer* sdl_renderer);

#endif // RENDERER_H