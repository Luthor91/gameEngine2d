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

#include "../Core/Animation/include/static_animation.h"
#include "../Core/Animation/include/dynamic_animation.h"

#include "../Core/Events/include/event_manager.h"

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

    Texture* texture_animation = Texture_Init(window->renderer, "Assets/Image/arrows_lgbt.png");
    Tilemap* tilemap_arrows = Tilemap_Init(window->renderer, 2, 4, &(Size2D){32, 32}, texture_animation);

    // Différentes positions de l'animation
    Transform* transforms[] = {
        Transform_Init(&(Point2D){0, 0}, NULL, NULL, 0, 0),
        Transform_Init(&(Point2D){550, 0}, NULL, NULL, 0, 0),
        Transform_Init(&(Point2D){0, 350}, NULL, NULL, 0, 0),
        Transform_Init(&(Point2D){550, 350}, NULL, NULL, 0, 0),
        Transform_Init(&(Point2D){550, 0}, NULL, NULL, 0, 0),
        Transform_Init(&(Point2D){0, 0}, NULL, NULL, 0, 0),
        Transform_Init(&(Point2D){0, 350}, NULL, NULL, 0, 0),
        Transform_Init(&(Point2D){300, 200}, NULL, NULL, 0, 0)
    };

    // Création de l'animation
    AnimationFrame** animation_frames = AnimationFrames_GenerateWithTransform(tilemap_arrows, transforms);
    AnimationSettings* animation_settings = AnimationSettings_Init(500, 8, 0);
    StaticAnimation* static_animation = StaticAnimation_Init(animation_frames, animation_settings);

    // Dispensable, utile seulement quand on a plusieurs animations du même type à afficher sur le même plan
    StaticAnimationManager* animation_manager = StaticAnimationManager_Init(1);
    StaticAnimationManager_Add(animation_manager, static_animation);

    // Permet de gérer l'affichage des objets affichables
    RendererManager* manager = RendererManager_Init(window->renderer, 10);
    Renderer* renderer_window = Renderer_Init(Renderer_Window, window, 0);
    Renderer* renderer_static_animation = Renderer_Init(Renderer_StaticAnimationManager, animation_manager, 1);

    // On ajoute tous les renderer au "manager"
    RendererManager_Add(manager, 2, renderer_window, renderer_static_animation);
    // On tri, ça permet de pouvoir afficher toutes les animations dans le bon ordre
    RendererManager_Sort(manager);

    SDL_Event event;
    int quit = 0;

    while (!quit) {

        Event_Exit(&quit);
        RendererManager_Render(manager); 
        Time_SetFPSLimit(60);
        
    }

    Exit_All(window);

    return 0;
}

