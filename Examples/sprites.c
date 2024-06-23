#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Core/UI/include/window.h"
#include "../Core/Graphics/include/texture.h"
#include "../Core/Graphics/include/sprite.h"
#include "../Core/Spatial/include/transform.h"
#include "../Core/Renderer/include/renderer.h"
#include "../Core/Utilities/include/time.h"
#include "../Core/Utilities/include/init.h"
#include "../Core/Utilities/include/string.h"

#include "../Core/Events/include/event_manager.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

int main(int argc, char* argv[]) {
    Uint32 start = Time_GetCurrentTime();
        
    Init_Env(".env");

    if (Init_All() != 0) {
        fprintf(stderr, "Main: %s\n", SDL_GetError());
        return 1;
    }

    Transform* transform_window = Transform_Init(NULL, &(Size2D){WINDOW_WIDTH, WINDOW_HEIGHT}, NULL, 0.0, 1.0);
    Window* window = Window_Init("Titre de la fenêtre.", transform_window, "Assets/Image/background1.jpg");
    Texture* texture = Texture_Init(window->renderer, "Assets/Image/cube.png");
    
    RendererManager* manager = RendererManager_Init(window->renderer, 1000*1000);
    Renderer* renderer_window = Renderer_Init(Renderer_Window, window, 0);
    RendererManager_Add(manager, 1, renderer_window);

    for (size_t i = 0, z = 0; i < 100; i++, z++) {
        if (z % 3 == 0) {  z = 1; }

        int random_x = rand() % WINDOW_WIDTH, random_y = rand() % WINDOW_HEIGHT;
        Transform* transform = Transform_Init(&(Point2D){random_x, random_y}, &(Size2D){32, 32}, NULL, 0, 0);
        Sprite* sprite = Sprite_Init(window->renderer, transform, texture);
        Renderer* renderer_sprite = Renderer_Init(Renderer_Sprite, sprite, z);
        RendererManager_Add(manager, 1, renderer_sprite);

    }
    
    RendererManager_Sort(manager);
    RendererManager_Flatten(manager);

    int quit = 0;
    printf("INITIALISATION : delai de %f seconds\n",Time_CalculateDeltaTime(Time_GetCurrentTime(), start));

    while (!quit) {
        break;
        Event_Exit(&quit);

        Uint32 start = Time_GetCurrentTime();
        RendererManager_Render(manager); 
        printf("RENDU : delai de %f seconds\n",Time_CalculateDeltaTime(Time_GetCurrentTime(), start));

        Time_SetFPSLimit(60);
    }

    Exit_All(window);

    return 0;
}

