#include "core.h"

// Dimensions de la fenêtre
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char* argv[]) {
    // Création de la fenêtre
    SDL_Window* window = createWindow("Titre de la Fenêtre");
    if (window == NULL) { return 1; }

    SDL_Renderer* renderer = createRenderer(window);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Boucle principale du programme
    int running = 1;
    SDL_Event event;
    while (running) {
        // Traitement des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0; // Sortir de la boucle si l'utilisateur ferme la fenêtre
            }
        }

        // Effacer l'écran avec une couleur noire
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
        SDL_RenderClear(renderer);

        // Dessiner ici...

        // Présenter le rendu à l'écran
        SDL_RenderPresent(renderer);
    }

    // Nettoyer et fermer SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
