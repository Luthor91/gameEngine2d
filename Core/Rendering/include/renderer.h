#ifndef RENDERER_H
#define RENDERER_H

typedef struct Renderer {
    void* renderFunction; // Pointeur vers la fonction de rendu
    void* object; // Pointeur vers l'objet spécifique
    SDL_Renderer* sdl_renderer;
} Renderer;

Renderer* Renderer_Init(void* renderFunction, void* object, SDL_Renderer* sdl_renderer);
void Renderer_DynamicAnimation(Renderer* renderer);
void Renderer_StaticAnimation(Renderer* renderer);
void Renderer_Sprite(Renderer* renderer);
void Render_Label(Renderer* renderer);

#endif // RENDERER_H