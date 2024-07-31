#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
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

// Cette valeur est le nombre d'objet idéal à afficher pour avoir 60 fps environ
#define IDEAL_RENDERED_OBJECTS 15000

#define CURRENT_RENDERED_OBJECTS 10

int main(int argc, char* argv[]) {
    Uint32 start = Time_GetCurrentTime();
    Init_Env(".env");

    if (Init_All() != 0) {
        fprintf(stderr, "Main: %s\n", SDL_GetError());
        return 1;
    }

    Transform* transform_window = Transform_Init(NULL, &(Size2D){WINDOW_WIDTH, WINDOW_HEIGHT}, NULL, 0.0, 1.0);
    Window* window = Window_Init(NULL, transform_window, NULL);
    Texture* texture = Texture_Init(window->renderer, NULL);
    
    RendererManager* manager = RendererManager_Init(window->renderer, CURRENT_RENDERED_OBJECTS+1);
    Renderer* renderer_window = Renderer_Init(Renderer_Window, window, 0);
    RendererManager_Add(manager, 1, renderer_window);

    for (int i = 0, z = 0; i < CURRENT_RENDERED_OBJECTS; i++, z++) {
        if (z % 3 == 0) {  z = 1; }

        int random_x = rand() % WINDOW_WIDTH, random_y = rand() % WINDOW_HEIGHT;
        Transform* transform = Transform_Init(&(Point2D){random_x, random_y}, &(Size2D){32, 32}, NULL, 0, 0);
        Sprite* sprite = Sprite_Init(transform, texture);
        Renderer* renderer_sprite = Renderer_Init(Renderer_Sprite, sprite, z);
        RendererManager_Add(manager, 1, renderer_sprite);

    }

    RendererManager_Sort(manager);

    // Vérifier si le RendererManager est trié correctement
    int sorted_correctly = 1;
    for (int i = 1; i < manager->current_renderer_count; i++) {
        if (manager->renderers[i]->z_index < manager->renderers[i - 1]->z_index) {
            sorted_correctly = 0;
            break;
        }
    }

    if (sorted_correctly) {
        printf("Le RendererManager est trié correctement par ordre croissant de z_index.\n");
    } else {
        printf("Erreur : Le RendererManager n'est pas trié correctement par ordre croissant de z_index.\n");
    }

    //RendererManager_Flatten(manager);

    int quit = 0;
    printf("INITIALISATION : %d objects in %f seconds\n", CURRENT_RENDERED_OBJECTS, Time_CalculateDeltaTime(Time_GetCurrentTime(), start));

    while (!quit) {
        Event_Exit(&quit);

        Uint32 start = Time_GetCurrentTime();
        RendererManager_Render(manager); 
        printf("RENDU : nb object:%d ; frametime:%fs ; fps:%2f\n", CURRENT_RENDERED_OBJECTS, Time_CalculateDeltaTime(Time_GetCurrentTime(), start), Time_GetFPS());

        Time_SetFPSLimit(60);
    }

    Exit_All(window);

    return 0;
}

