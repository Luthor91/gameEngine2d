#include "../include/event_manager.h"

void Event_Exit(int* quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *quit = 1;
        }
    }
}
