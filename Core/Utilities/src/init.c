#include "../include/init.h"

// Fonction pour charger les variables d'environnement à partir d'un fichier .env
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

int Init_All() {
    
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Main: %s\n", SDL_GetError());
        return 1;
    }

    // Initialiser SDL_ttf si ce n'est pas déjà fait
    if (!TTF_WasInit() && TTF_Init() == -1) {
        fprintf(stderr, "Main: %s\n", TTF_GetError());
        return 0;
    }

    // Initialiser SDL_image avec les formats JPG et PNG
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Main: %s\n", IMG_GetError());
        return 1;
    }

    return 0; // Succès
}

void Exit_All(Window* window) {
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->sdl_window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}