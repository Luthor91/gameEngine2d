#include "../include/init_engine.h"

int Init_All() {
    srand((unsigned int)time(NULL)); // Casting pour éviter les avertissements

    if (Init_entity_attributes() == 0) {
        fprintf(stderr, "Error: Failed to init entities attributes\n");
        return 0;
    }

    if (Init_event_types() == 0) {
        fprintf(stderr, "Error: Failed to init events types\n");
        return 0;
    }
    
    game.window = createWindow("Game Window");
    if (game.window == NULL) {
        fprintf(stderr, "Error: Failed to create window\n");
        return 0;
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

int Init_entity_attributes() {
    // Allouer dynamiquement chaque tableau
    entityStates = (bool *)malloc(MAX_ENTITIES * sizeof(bool));
    hasSprite = (bool *)malloc(MAX_ENTITIES * sizeof(bool));
    hasPosition = (bool *)malloc(MAX_ENTITIES * sizeof(bool));
    hasVelocity = (bool *)malloc(MAX_ENTITIES * sizeof(bool));
    hasInput = (bool *)malloc(MAX_ENTITIES * sizeof(bool));
    hasTransform = (bool *)malloc(MAX_ENTITIES * sizeof(bool));
    hasAnimation = (bool *)malloc(MAX_ENTITIES * sizeof(bool));
    hasHitbox = (bool *)malloc(MAX_ENTITIES * sizeof(bool));
    hasSize = (bool *)malloc(MAX_ENTITIES * sizeof(bool));
    hasTags = (bool *)malloc(MAX_ENTITIES * sizeof(bool));
    hasDatas = (bool *)malloc(MAX_ENTITIES * sizeof(bool));

    game = (GameGlobals){ NULL, NULL , 800, 600 };

    // Vérification que l'allocation a bien fonctionné pour chaque tableau
    if (!entityStates || !hasSprite || !hasPosition || !hasVelocity ||
        !hasInput || !hasTransform || !hasAnimation || !hasHitbox ||
        !hasSize || !hasTags || !hasDatas) {
        fprintf(stderr, "Error: Init attributes entity failed.\n");
        return 0;
    }

    // Initialisation des tableaux à false
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entityStates[i] = false;
        hasSprite[i] = false;
        hasPosition[i] = false;
        hasVelocity[i] = false;
        hasInput[i] = false;
        hasTransform[i] = false;
        hasAnimation[i] = false;
        hasHitbox[i] = false;
        hasSize[i] = false;
        hasTags[i] = false;
        hasDatas[i] = false;
    }

    return 1;
}
