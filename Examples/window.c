#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Core/UI/include/window.h"
#include "../Core/Graphics/include/texture.h"
#include "../Core/Spatial/include/transform.h"
#include "../Core/Renderer/include/renderer.h"

#define WINDOW_WIDTH 200
#define WINDOW_HEIGHT 100

void Renderer_Window(Renderer* renderer, SDL_Renderer* sdl_renderer) {
    Window* window = (Window*)renderer->object;
    SDL_RenderCopy(sdl_renderer, window->texture->sdl_texture, NULL, NULL);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Main: %s\n", SDL_GetError());
        return 1;
    }
    
    if (!Font_Start()) {
        printf("Main: Erreur initialisation police d'écriture\n");
        return 1;
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Main: %s\n", IMG_GetError());
        return 1;
    }

    Transform* transform_window = Transform_Init(&(Point2D){0, 0}, &(Size2D){WINDOW_WIDTH, WINDOW_HEIGHT}, &(Point2D){0, 0}, 0.0, 1.0);
    Window* window = Window_Init("Titre de la fenêtre.", transform_window, "../Assets/Image/background1.jpg");
    
    // Initialiser RendererManager
    RendererManager* manager = RendererManager_Init(window->renderer, 10); // 10 est un exemple pour max_renderers

    // Initialiser Renderer et l'ajouter au RendererManager
    Renderer* renderer = Renderer_Init(Renderer_Window, window, 0); // z_index 0 pour cette fenêtre
    RendererManager_Add(manager, renderer);

    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_RenderClear(window->renderer);

        // Rendre tous les renderers dans le manager
        RendererManager_Render(manager);

        SDL_RenderPresent(window->renderer);
    }

    // Libération des ressources
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->sdl_window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
