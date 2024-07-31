#include <stdio.h>
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour time()

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Core/UI/include/window.h"
#include "../Core/Graphics/include/texture.h"
#include "../Core/Spatial/include/transform.h"
#include "../Core/Renderer/include/renderer.h"
#include "../Core/Utilities/include/time.h"
#include "../Core/Utilities/include/init.h"
#include "../Core/Utilities/include/string.h"

#include "../Core/Animation/include/static_animation.h"
#include "../Core/Animation/include/dynamic_animation.h"

#include "../Core/Events/include/event_manager.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400
#define CURRENT_RENDERED_ANIMATIONS 15000

int main(int argc, char* argv[]) {
    Uint32 start = Time_GetCurrentTime();
    Init_Env(".env");

    if (Init_All() != 0) {
        fprintf(stderr, "Main: %s\n", SDL_GetError());
        return 1;
    }

    Transform* transform_window = Transform_Init(&(Point2D){0, 0}, &(Size2D){WINDOW_WIDTH, WINDOW_HEIGHT}, &(Point2D){0, 0}, 0.0, 1.0);
    Window* window = Window_Init("Titre de la fenêtre.", transform_window, "Assets/Image/background1.jpg");

    Texture* texture_animation = Texture_Init(window->renderer, "Assets/Image/arrows_lgbt.png");
    Tilemap* tilemap_arrows = Tilemap_Init(window->renderer, 2, 4, &(Size2D){32, 32}, texture_animation);

    RendererManager* manager = RendererManager_Init(window->renderer, CURRENT_RENDERED_ANIMATIONS + 1);
    Renderer* renderer_window = Renderer_Init(Renderer_Window, window, 0);
    RendererManager_Add(manager, 1, renderer_window);

    // Initialiser le générateur de nombres aléatoires
    srand((unsigned int)time(NULL));

    // Création d'un tableau pour les animations
    StaticAnimation* static_animations[CURRENT_RENDERED_ANIMATIONS];

    for (int i = 0; i < CURRENT_RENDERED_ANIMATIONS; i++) {
        // Générer des positions aléatoires
        int x = rand() % (WINDOW_WIDTH - 32);
        int y = rand() % (WINDOW_HEIGHT - 32);

        // Différentes positions de l'animation
        Transform* transforms[] = {
            Transform_Init(&(Point2D){x, y}, NULL, NULL, 0, 0),
            Transform_Init(&(Point2D){x + 32, y}, NULL, NULL, 0, 0),
            Transform_Init(&(Point2D){x, y + 32}, NULL, NULL, 0, 0),
            Transform_Init(&(Point2D){x + 32, y + 32}, NULL, NULL, 0, 0),
            Transform_Init(&(Point2D){x + 32, y}, NULL, NULL, 0, 0),
            Transform_Init(&(Point2D){x, y}, NULL, NULL, 0, 0),
            Transform_Init(&(Point2D){x, y + 32}, NULL, NULL, 0, 0),
            Transform_Init(&(Point2D){x + 16, y + 16}, NULL, NULL, 0, 0)
        };

        // Création de l'animation
        AnimationFrame** animation_frames = AnimationFrames_GenerateWithTransform(tilemap_arrows, transforms);
        AnimationSettings* animation_settings = AnimationSettings_Init(125, 8, 3); // 3ème paramètre à 2 pour reboucler à l'infini
        static_animations[i] = StaticAnimation_Init(animation_frames, animation_settings);

        // Initialiser les renderers pour les animations
        Renderer* renderer = Renderer_Init(Renderer_StaticAnimation, static_animations[i], i + 1);
        RendererManager_Add(manager, 1, renderer);
    }

    // On tri, ça permet de pouvoir afficher toutes les animations dans le bon ordre
    RendererManager_Sort(manager);

    SDL_Event event;
    int quit = 0;
    printf("INITIALISATION : %d objects in %f seconds\n", CURRENT_RENDERED_ANIMATIONS, Time_CalculateDeltaTime(Time_GetCurrentTime(), start));

    while (!quit) {
        Event_Exit(&quit);

        Uint32 start = Time_GetCurrentTime();
        RendererManager_Render(manager);
        printf("RENDU : nb object:%d ; frametime:%fs ; fps:%2f\n", CURRENT_RENDERED_ANIMATIONS, Time_CalculateDeltaTime(Time_GetCurrentTime(), start), Time_GetFPS());

        Time_SetFPSLimit(60);
    }

    Exit_All(window);

    return 0;
}
