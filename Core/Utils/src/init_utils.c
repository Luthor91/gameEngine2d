#include "../include/init_utils.h"

int Init_All() {
    srand((unsigned int)time(NULL)); // Casting pour éviter les avertissements
    initializeEventTypes();
    
    game.window = createWindow("Game Window");
    if (game.window == NULL) {
        fprintf(stderr, "Error: Failed to create window\n");
        return 0; // Échec
    }
    
    game.renderer = createRenderer(game.window);
    if (game.renderer == NULL) {
        fprintf(stderr, "Error: Failed to create renderer\n");
        SDL_DestroyWindow(game.window); // Nettoyage avant retour
        return 0; // Échec
    }
    
    initStateMachine();
    if (Init_Dependancies() == 0) {
        SDL_DestroyRenderer(game.renderer); // Nettoyage en cas d'échec
        SDL_DestroyWindow(game.window);
        return 0; // Échec
    }
    
    return 1; // Succès
}

int Init_Dependancies() {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 0;
    }

    // Initialiser SDL_ttf si ce n'est pas déjà fait
    if (!TTF_WasInit() && TTF_Init() == -1) {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        SDL_Quit(); // Nettoyage en cas d'échec
        return 0;
    }

    // Initialiser SDL_image avec les formats JPG et PNG
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());
        TTF_Quit(); // Nettoyage en cas d'échec
        SDL_Quit(); // Nettoyage en cas d'échec
        return 0;
    }

    // Initialiser SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        fprintf(stderr, "Mix_OpenAudio Error: %s\n", Mix_GetError());
        IMG_Quit(); // Nettoyage en cas d'échec
        TTF_Quit(); // Nettoyage en cas d'échec
        SDL_Quit(); // Nettoyage en cas d'échec
        return 0;
    }

    Time_Initialize();
    
    return 1; // Succès
}

void Exit_All() {
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}