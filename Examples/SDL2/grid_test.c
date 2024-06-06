//  gcc -I/usr/include/SDL2 -o button_test Examples/SDL2/button_test.c  Core/Graphics/src/button.c Core/Graphics/src/window.c Core/Graphics/src/sprite.c Core/Graphics/src/label.c -lSDL2 -lSDL2_image -lm && ./button_test
// gcc -O3 -g -Wall -Wextra -std=c89 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -I/usr/include/SDL2 -o button_test Examples/SDL2/button_test.c  Core/Graphics/src/button.c Core/Graphics/src/window.c Core/Graphics/src/sprite.c Core/Graphics/src/label.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm && ./button_test

// gcc -I/usr/include/SDL2 -o grid_test Examples/SDL2/grid_test.c Core/Graphics/src/window.c Core/Graphics/src/sprite.c Core/Graphics/src/label.c Core/Graphics/src/aspect.c Core/Graphics/src/font.c Core/Graphics/src/gridcell.c Core/Graphics/src/grid.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm && ./grid_test

#include "../../Core/Graphics/include/window.h"
#include "../../Core/Graphics/include/label.h"
#include "../../Core/Graphics/include/sprite.h"
#include "../../Core/Graphics/include/grid.h"
#include "../../Core/Graphics/include/font.h"

/****************************
    Fonction utilisé lors de l'appuie du bouton
***************************/

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Main: %s\n", SDL_GetError());
        return 1;
    }
    
    if (!Font_Start()) {
        printf("Main: Erreur initialisation police d'écriture\n");
        return 1;
    }

    /****************************
        Bloc de code pour afficher une fenêtre
    ***************************/
    Aspect* aspect_window = Aspect_Init(&(SDL_Rect){0, 0, 720, 480}, &(SDL_Point){360, 240}, 1.0, 0.0);
    Window* window = Window_Init("Window Test", aspect_window, "Assets/Image/background1.jpg");

    SDL_Renderer* renderer = Window_GetRenderer(window);
    
    Grid* grid = Grid_Init(5, 5);
    Grid_Generate(grid);
    
    int max_cells = grid->number_cells;
    for (int i = 0; i < max_cells; i++) {
        Sprite* sprite = Sprite_Init(renderer, NULL, "Assets/Image/background1.jpg");
        Cell_SetSprite(grid->cells[i], sprite);
    }

    for (int i = -max_cells*2; i < max_cells*2; i++) {
        Cell* cell = Grid_GetCell(grid, i);
        if(!cell) {
            break;
        }    
    }

    int isRunning = 1;
    SDL_Event event;

    while (isRunning) {
   
        while ( SDL_PollEvent(&event) )  {

            if (event.type == SDL_QUIT) {
               isRunning = 0;
            }
        }

    /****************************
        On efface le rendu de l'écran
        On affiche la fenêtre
        On affiche tous les sprites
        On met à jour l'écran
    ***************************/
        SDL_RenderClear(window->renderer);

        Sprite_RenderStatic(window->sprite, renderer);
        
        Grid_Render(grid, renderer);
        SDL_RenderPresent(window->renderer);        

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    SDL_Quit();

    return 0;
}
