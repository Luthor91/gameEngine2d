//  gcc -I/usr/include/SDL2 -o button_test Examples/SDL2/button_test.c  Core/Graphics/src/button.c Core/Graphics/src/window.c Core/Graphics/src/sprite.c Core/Graphics/src/renderer.c -lSDL2 -lSDL2_image -lm && ./button_test

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
        La création du renderer est obligatoire pour chaque fenêtre
    ***************************/
    Window* window = Window_Create("Window Test", 0, 0, 960, 1080);
    SDL_Renderer* renderer = Window_CreateRenderer(window);
    
    /****************************
        Bloc de code pour afficher une fenêtre
    ***************************/
    Window_SetSprite(window, renderer, "Assets/Image/background1.jpg");
    Sprite_SetRectangle(window->sprite, (SDL_Rect){ 0, 0, 960, 1080} );
    Window_SyncRectWithSprite(window);


    int total_button = 600;
    int x = 0;
    int y = 0;
    Sprite** sprites = malloc(total_button * sizeof(Sprite*));
    Button** buttons = malloc(total_button * sizeof(Button*));
    
    // x=x+35 permet d'incrémenter la position des nouveaux élements
    for (long i = 0; i < total_button; i++, x=x+35) {

        Button* button = Button_Create(0, 0, 10, 10);
        Button_SetSprite(button, renderer, "Assets/Image/button2.png");

        if (i % 31 == 0 && i != 0) {
            x = 0;
            y = y + 10;
        }

        Sprite_SetRectangle(button->sprite, (SDL_Rect){ x, y, 30, 30} );
        Sprite_SetScale(button->sprite, i/20);
        Button_SetOnClick(button, onClick, (void*)i);
        Button_SyncRectWithSprite(button);

        sprites[i] = button->sprite;
        buttons[i] = button;

    }

    int running = 1;
    SDL_Event event;

    while (running) {
   
        while ( SDL_PollEvent(&event) )  {
            switch (event.type) {
                case SDL_WINDOWEVENT:
                    if (event.window.event==SDL_WINDOWEVENT_CLOSE) {
                        running = 0;
                    }
                case SDL_MOUSEBUTTONDOWN:
                    for (int i = 0; i < total_button; i++) {
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
        Window_Render(window, renderer);
        Sprite_RenderAll(sprites, total_button, renderer);
        SDL_RenderPresent(renderer);        

        SDL_Delay(10);
    }

    SDL_Quit();

    return 0;
}
