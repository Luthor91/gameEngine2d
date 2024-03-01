//  gcc -I/usr/include/SDL2 -o button_test Examples/SDL2/button_test.c  Core/Graphics/src/button.c Core/Graphics/src/window.c Core/Graphics/src/sprite.c -lSDL2 -lSDL2_image -lm && ./button_test

#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../Core/Graphics/include/window.h"
#include "../../Core/Graphics/include/button.h"
#include "../../Core/Graphics/include/sprite.h"

/****************************
    Fonction utilisé lors de l'appuie du bouton
***************************/
void onClick(void* data) {
    printf("Button pressed, data : %ld\n", (long)data);
}

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    /****************************
        Bloc de code pour afficher une fenêtre
    ***************************/
    Window* window = Window_Init("Window Test", (SDL_Rect){0, 0, 720, 480}, "Assets/Image/background1.jpg", (SDL_Point){360, 240}, 1.0, 0.0); // here
    SDL_Renderer* renderer = Window_GetRenderer(window);
    
    int total_button = 5; // Nombre de bouton = total_button - 1
    int x = 0, y = 0;
    Sprite** sprites = malloc(total_button * sizeof(Sprite*));
    Button** buttons = malloc(total_button * sizeof(Button*));
    
    // x=x+35 permet d'incrémenter la position des nouveaux élements
    for (long i = 0; i < total_button; i++, x=x+100) {

        if (i % 7 == 0 && i != 0) {
            x = 0;
            y = y + 50;
        }

        Sprite* sprite = Sprite_Init(renderer, "Assets/Image/button2.png", (SDL_Rect){200, 200, 30, 30}, (SDL_Point){360, 240}, 1, 1.0*i);
        Button* button = Button_InheritSprite(sprite, onClick, (void*)i);
        
        sprites[i] = button->sprite;
        buttons[i] = button;

        printf("x:%d, y:%d, w:%d, h:%d\n", button->sprite->rect.x, button->sprite->rect.y, button->sprite->rect.w, button->sprite->rect.h);

    }

    int isRunning = 1;
    SDL_Event event;

    while (isRunning) {
   
        while ( SDL_PollEvent(&event) )  {
            switch (event.type) {
                case SDL_QUIT: 
                    isRunning = 0;
                case SDL_MOUSEBUTTONDOWN:
                    for (int i = 0; i < total_button; i++) {
                        // Attention, la rotation de l'élement n'est pas prise en compte pour le moment pour le clic !
                        Button_IsPressed(buttons[i], event.button.x,event.button.y);
                    }
            }
        }

    /****************************
        On efface le rendu de l'écran
        On affiche la fenêtre
        On affiche tous les sprites
        On met à jour l'écran
    ***************************/
        SDL_RenderClear(renderer);
        Sprite_RenderStatic(window->sprite, renderer);
        Sprites_RenderTransformable(sprites, total_button, renderer, (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL));
        SDL_RenderPresent(renderer);        

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window->window);
    SDL_Quit();

    return 0;
}
