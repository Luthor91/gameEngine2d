#include "../include/init_utils.h"

int Init_All() {
    srand(time(NULL));
    initializeEventTypes();
    g_window = createWindow("Game Window");
    g_renderer = createRenderer(g_window);
    initStateMachine();
    if (Init_Dependancies == 0) { return 0; }
    
    return 1;
}

int Init_Dependancies() {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Main: %s\n", SDL_GetError());
        return 0;
    }

    // Initialiser SDL_ttf si ce n'est pas déjà fait
    if (!TTF_WasInit() && TTF_Init() == -1) {
        fprintf(stderr, "Main: %s\n", TTF_GetError());
        return 0;
    }

    // Initialiser SDL_image avec les formats JPG et PNG
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Main: %s\n", IMG_GetError());
        return 0;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 0;
    }

    Time_Initialize();

    return 1; // Succès
}

void Exit_All() {
    //SDL_DestroyRenderer(window->renderer);
    //SDL_DestroyWindow(window->sdl_window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}