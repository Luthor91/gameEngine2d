// gcc -I/usr/include/SDL2 -o tilemap_test Examples/SDL2/tilemap_test.c Core/Graphics/src/window.c Core/Graphics/src/sprite.c Core/Graphics/src/label.c Core/Graphics/src/transform.c Core/Graphics/src/font.c Core/Graphics/src/tilemap.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm && ./tilemap_test

#include "../../Core/Graphics/include/window.h"
#include "../../Core/Graphics/include/label.h"
#include "../../Core/Graphics/include/sprite.h"
#include "../../Core/Graphics/include/transform.h"
#include "../../Core/Graphics/include/tilemap.h"
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
    int window_width = 1080;
    int window_height = 960;
    int tile_size = 5;
    Transform* transform_window = Transform_Init(&(SDL_Rect){0, 0, window_width, window_height}, &(SDL_Point){360, 240}, 1.0, 0.0);
    Window* window = Window_Init("Window Test", transform_window, "Assets/Image/background1.jpg");

    SDL_Renderer* renderer = Window_GetRenderer(window);
    
    Tilemap* tilemap = Tilemap_Init(window->sprite, tile_size, tile_size);

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

        //Sprite_RenderStatic(window->sprite, renderer);
        int i = 0;
        
        for(int y = 0; y < window_height/tile_size; y++) {
            for(int x = 0; x < window_width/tile_size; x++) {
                Tilemap_RenderTile(tilemap, renderer, i, tile_size*x, tile_size*y);
                i++;
            }
        }
        
        SDL_RenderPresent(window->renderer);        

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    SDL_Quit();

    return 0;
}
