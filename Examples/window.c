#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Core/UI/include/window.h"
#include "../Core/Graphics/include/texture.h"
#include "../Core/Spatial/include/transform.h"
#include "../Core/Renderer/include/renderer.h"
#include "../Core/Utilities/include/time.h"
#include "../Core/Utilities/include/init.h"
#include "../Core/Utilities/include/string.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

int main(int argc, char* argv[]) {

    Init_Env(".env");

    if (Init_All() != 0) {
        fprintf(stderr, "Main: %s\n", SDL_GetError());
        return 1;
    }
    Transform* transform_window = Transform_Init(&(Point2D){0, 0}, &(Size2D){WINDOW_WIDTH, WINDOW_HEIGHT}, &(Point2D){0, 0}, 0.0, 1.0);
    Window* window = Window_Init("Titre de la fenêtre.", transform_window, "Assets/Image/background1.jpg");

    RendererManager* manager = RendererManager_Init(window->renderer, 10);
    Renderer* renderer = Renderer_Init(Renderer_Window, window, 0);
    RendererManager_Add(manager, 1, renderer);
    
    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        RendererManager_Render(manager);
        Time_SetFPSLimit(60);
    }

    Exit_All(window);

    return 0;
}
