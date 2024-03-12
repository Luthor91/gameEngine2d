//  gcc -I/usr/include/SDL2 -o button_test Examples/SDL2/button_test.c  Core/Graphics/src/button.c Core/Graphics/src/window.c Core/Graphics/src/sprite.c Core/Graphics/src/transform.c Core/Graphics/src/label.c  Core/Graphics/src/font.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm && ./button_test

// gcc -O3 -g -Wall -Wextra -std=c89 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -I/usr/include/SDL2 -o button_test Examples/SDL2/button_test.c  Core/Graphics/src/button.c Core/Graphics/src/window.c Core/Graphics/src/sprite.c Core/Graphics/src/label.c -lSDL2 -lSDL2_image -lSDL2_ttf -lm && ./button_test

#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../Core/Graphics/include/window.h"
#include "../../Core/Graphics/include/button.h"
#include "../../Core/Graphics/include/sprite.h"
#include "../../Core/Graphics/include/transform.h"

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
    Transform* transform_window = Transform_Init(&(SDL_Rect){0, 0, 720, 480}, &(SDL_Point){360, 240}, 1.0, 0.0);
    Window* window = Window_Init("Window Test", transform_window, "Assets/Image/background1.jpg");
    SDL_Renderer* renderer = Window_GetRenderer(window);
    
    int total_button = 5;
    int x = 0; int y = 0;
    Sprite** sprites = malloc(total_button * sizeof(Sprite*));
    Button** buttons = malloc(total_button * sizeof(Button*));
    
    // x=x+35 permet d'incrémenter la position des nouveaux élements
    printf("Window : \n\tx:%d, y:%d, w:%d, h:%d\n", window->sprite->transform->bounds->x, window->sprite->transform->bounds->y, window->sprite->transform->bounds->w, window->sprite->transform->bounds->h);

    for (long i = 0; i < total_button; i++, x=x+100) {

        if (i % 7 == 0 && i != 0) {
            x = 0;
            y = y + 50;
        }
        Transform* transform_sprite = Transform_Init(&(SDL_Rect){200+10*i, 200, 30, 30}, &(SDL_Point){360, 240}, 1, 1.0);
        Sprite* sprite = Sprite_Init(renderer, transform_sprite, "Assets/Image/button2.png");
        Button* button = Button_InheritSprite(sprite, onClick, (void*)i);
        
        sprites[i] = button->sprite;
        buttons[i] = button;

        printf("Button : \n\tx:%d, y:%d, w:%d, h:%d\n", button->sprite->transform->bounds->x, button->sprite->transform->bounds->y, button->sprite->transform->bounds->w, button->sprite->transform->bounds->h);

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
        
        for (size_t i = 0; i < total_button; i++) {
            Sprite_Render(sprites[i], renderer, (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL));
        }
        
        SDL_RenderPresent(renderer);        

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window->window);
    SDL_Quit();

    return 0;
}
