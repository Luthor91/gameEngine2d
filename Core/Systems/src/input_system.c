#include "../include/input_system.h"
#include <SDL2/SDL.h>

void updateInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) { exit(0); }

        for (Entity entity = 0; entity < getEntityCount(); ++entity) {
            if (!hasInput[entity]) { continue; }  

            InputComponent* input = getInputComponent(entity);
            if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                bool isPressed = (event.type == SDL_KEYDOWN);
                SDL_Keycode key = event.key.keysym.sym;
                if (key < MAX_KEYS) {
                    input->keys[key] = isPressed;
                }
            }
        }
    }
}
