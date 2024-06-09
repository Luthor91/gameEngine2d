// gcc -I/usr/include/SDL2 -o physics_test Examples/SDL2/physics_test.c Core/Graphics/src/sprite.c Core/Graphics/src/aspect.c Core/Graphics/src/window.c Core/Physics/src/rigidbody.c Core/Physics/include/core_physics.h Core/Graphics/include/core_graphics.h Core/Physics/src/transform.c Core/Physics/src/rigidbody.c Core/Physics/src/staticbody.c Core/Physics/src/characterbody.c -lSDL2 -lSDL2_image -lm && ./physics_test

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

#include "../../Core/Graphics/include/animated_sprite.h"
#include "../../Core/Physics/include/core_physics.h"
#include "../../Core/Graphics/include/core_graphics.h"
#include "../../Core/Physics/include/rigidbody.h"
#include "../../Core/Physics/include/staticbody.h"
#include "../../Core/Physics/include/characterbody.h"
#include "../../Core/Physics/include/material.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32
#define NUM_SPRITES 8
#define ANIMATION_SPEED 100
#define FPS_LIMIT_RATE 16.66666666666667
#define MAX_ANIMATION 10
#define MAX_RIGID_BODY 10

int main(int argc, char* argv[]) {

    Aspect* aspect_window = Aspect_Init(&(SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, NULL, 0, 0);
    Window* window = Window_Init("Sprite Animation", aspect_window, "Assets/Image/background1.jpg");
    SDL_Renderer* renderer = Window_GetRenderer(window);
    
    Aspect* aspect_sprite = Aspect_Init(&(SDL_Rect){0, 0, 32, 32}, &(SDL_Point){0, 0}, 0, 0);
    Transform* transform_sprite = Transform_Init(&(Point2D){0, 0}, &(Size2D){32, 32}, &(Point2D){16, 16}, 0, 0);

    Acceleration* accel = Acceleration_Init(0.0f, 0.0f);  // Accélération en m/s^2

    ForceManager* forceManager = ForceManager_Init(2);
    Force* gravity = Force_Init(9.81f, PI/2);
    Force* externalForce = Force_Init(9.81f, 3*PI/2);
    ForceManager_AddForce(forceManager, gravity);
    ForceManager_AddForce(forceManager, externalForce);

    ImpulseManager* impulseManager = ImpulseManager_Init(10);

    Velocity* velocity = Velocity_Init(0.0f, 1.0f);  // Vitesse en m/s
    Material* material = Material_Init(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);  // Propriétés matérielles, incluant la masse
    Physics* physics = Physics_Init(accel, forceManager, impulseManager, velocity, material);

    RigidBody* body = RigidBody_Init(transform_sprite, physics);

    Sprite* sprite = Sprite_Init(renderer, aspect_sprite, "Assets/Image/black_cubes.png");
    
    SDL_Event event;
    int quit = 0;

    // Variables pour le calcul de deltaTime
    Uint32 current_time = SDL_GetTicks();
    Uint32 previous_time = current_time;
    float deltaTime = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    // Créer une impulsion de 0.5 secondes vers l'Est (0 radians)
                    Impulse* impulse = Impulse_Init(5.0f, 0.0f, 0.5f); // Vous pouvez ajuster la magnitude
                    ImpulseManager_AddImpulse(body->physics->impulses, impulse);
                }
            }
        }

        // Calcul de deltaTime
        current_time = SDL_GetTicks();
        deltaTime = (current_time - previous_time) / 1000.0f;  // Convertir de ms à s
        previous_time = current_time;

        SDL_RenderClear(renderer);
        Sprite_RenderStatic(window->sprite, renderer);  
        RigidBody_Update(body, deltaTime);
        
        sprite->aspect->bounds->x = body->transform->position->x;
        sprite->aspect->bounds->y = body->transform->position->y;

        Sprite_Render(sprite, renderer, SDL_FLIP_NONE);

        SDL_RenderPresent(renderer);
        SDL_Delay(FPS_LIMIT_RATE); // Delay to limit frame rate
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window->window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}