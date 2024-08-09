#include "../include/init.h"

int Init_All() {
    
    if (Init_Dependancies == 0) { return 0; }
    Init_Env(".env");
    Init_Global();
    
    return 1;
}

void Init_Env(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Init : Erreur lors de l'ouverture du fichier %s.\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Ignore les lignes vides ou celles qui commencent par #
        if (line[0] == '\0' || line[0] == '\n' || line[0] == '#') {
            continue;
        }

        // Recherche du signe égal pour séparer le nom de la variable de sa valeur
        char *equal_sign = strchr(line, '=');
        if (equal_sign != NULL) {
            // Remplace le signe égal par un caractère nul pour séparer les deux parties
            *equal_sign = '\0';

            // La partie avant le signe égal est le nom de la variable
            char *name = line;

            // La partie après le signe égal est la valeur de la variable
            char *value = equal_sign + 1;
            // Supprime le caractère de saut de ligne à la fin de la valeur
            value[strcspn(value, "\n")] = '\0';

            // Définit la variable d'environnement
            setenv(name, value, 1);
        }
    }

    fclose(file);
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

    Time_Initialize();

    return 1; // Succès
}

void Init_Global() {
    CURRENT_WINDOW = DEFAULT_WINDOW;
    TIMER_MANAGER = DEFAULT_TIMER;
    RENDERER_MANAGER = DEFAULT_RENDERER;
    CHARACTERBODY_MANAGER = DEFAULT_CHARACTERBODY;
    RIGIDBODY_MANAGER = DEFAULT_RIGIDBODY;
    STATICBODY_MANAGER = DEFAULT_STATICBODY;
    PHYSICSBODIES_MANAGER = PhysicBodies_Init(CHARACTERBODY_MANAGER, RIGIDBODY_MANAGER, STATICBODY_MANAGER);
    EVENT_MANAGER = DEFAULT_EVENT;
    TIMER_MANAGER = DEFAULT_TIMER;
    WORLD_PHYSICS = DEFAULT_WORLDPHYSICS;
}

void Exit_All(Window* window) {
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->sdl_window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}