//  gcc -I/usr/include/SDL2 -o button_test Examples/SDL2/button_test.c  Core/Graphics/src/button.c Core/Graphics/src/window.c Core/Graphics/src/sprite.c Core/Graphics/src/label.c -lSDL2 -lSDL2_image -lm && ./button_test
// gcc -O3 -g -Wall -Wextra -std=c89 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -I/usr/include/SDL2 -o button_test Examples/SDL2/button_test.c  Core/Graphics/src/button.c Core/Graphics/src/window.c Core/Graphics/src/sprite.c Core/Graphics/src/label.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm && ./button_test

// gcc -I/usr/include/SDL2 -o label_test Examples/SDL2/label_test.c Core/Graphics/src/window.c Core/Graphics/src/sprite.c Core/Graphics/src/label.c Core/Graphics/src/transform.c Core/Graphics/src/font.c Core/Graphics/src/cell.c Core/Graphics/src/grid.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm && ./label_test

#include "../../Core/Graphics/include/window.h"
#include "../../Core/Graphics/include/label.h"
#include "../../Core/Graphics/include/sprite.h"
#include "../../Core/Graphics/include/transform.h"
#include "../../Core/Graphics/include/cell.h"
#include "../../Core/Graphics/include/grid.h"
#include "../../Core/Graphics/include/font.h"

/****************************
    Fonction utilisé lors de l'appuie du bouton
***************************/
void onClick(void* data) {
    printf("Button pressed, data : %ld\n", (long)data);
}

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
    Transform* transform_window = Transform_Init(&(SDL_Rect){0, 0, 720, 480}, &(SDL_Point){360, 240}, 0.0, 0.0);
    Window* window = Window_Init("Window Test", transform_window, "Assets/Image/background1.jpg");

    Font* font = Font_Init(&(SDL_Color){255, 255, 0}, "Assets/Fonts/Open_Sans/OpenSans-Regular.ttf", 25);
    Transform* transform_label = Transform_Init(&(SDL_Rect){32, 32, 50, 50}, &(SDL_Point){360, 240}, 5.0, 1.0);
    Label* label = Label_Init(transform_label, font, "0");  

    SDL_Renderer* renderer = Window_GetRenderer(window);

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

        Sprite_RenderCut(window->sprite, renderer, &(SDL_Rect){0, 0, 300, 300});
        Label_RendererTransformable(label, window->renderer, SDL_FLIP_NONE);

        SDL_RenderPresent(window->renderer);        

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    SDL_Quit();

    return 0;
}
