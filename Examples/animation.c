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

    Texture* texture_animation = Texture_Init(window->renderer, "Assets/Image/black_cubes.png");
    Transform* transform_animation1 = Transform_Init(&(Point2D){0, 0}, &(Size2D){10, 10}, &(Point2D){0, 0}, 0.0, 0.0);
    Transform* transform_animation2 = Transform_Init(&(Point2D){400, 300}, &(Size2D){10, 10}, &(Point2D){0, 0}, 0.0, 0.0);

    AnimationFrame* frame1 = AnimationFrame_Init(0, texture_animation, transform_animation1);
    AnimationFrame* frame2 = AnimationFrame_Init(1, texture_animation, transform_animation2);
    AnimationFrame* animation_frames[] = { frame1, frame2 };

    AnimationSettings* animation_settings = AnimationSettings_Init(50, 2, false);
    StaticAnimation* static_animation = StaticAnimation_Init(animation_frames, animation_settings);

    StaticAnimationManager* animation_manager = StaticAnimationManager_Init(2);
    StaticAnimationManager_Add(animation_manager, static_animation);

    RendererManager* manager = RendererManager_Init(window->renderer, 10);
    Renderer* renderer_window = Renderer_Init(Renderer_Window, window, 0);
    Renderer* renderer_static_animation = Renderer_Init(Renderer_StaticAnimationManager, animation_manager, 1);

    RendererManager_Add(manager, 2, renderer_window, renderer_static_animation);
    RendererManager_Sort(manager);

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