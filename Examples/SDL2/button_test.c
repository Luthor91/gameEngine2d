//  gcc -I/usr/include/SDL2 -o button_test Examples/SDL2/button_test.c  Core/Graphics/src/button1.c Core/Graphics/src/window.c Core/Graphics/src/sprite.c -lSDL2 -lSDL2_image -lm && ./button_test

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../Core/Graphics/include/window.h"
#include "../../Core/Graphics/include/button.h"
#include "../../Core/Graphics/include/sprite.h"
#include "../../Core/Graphics/include/renderer.h"

void onClick() {

    printf("Button pressed, exit now\n");
}

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    Window* window = Window_Create("Window Test", 640, 480 );
    Window_LoadTexture(window, "Assets/Image/background1.jpg");

    int total_button = 1;

    Sprite** sprites = malloc(total_button * sizeof(Sprite*));

    for (int i = 0; i < total_button; i++) {
        SDL_Renderer* renderer = Window_GetRenderer(window->window);
        
        Button* button = Button_Create(renderer, 50, 50, 100, 100, NULL, NULL);
        
        sprites[i] = Button_SetSprite(button, renderer, "Assets/Image/button2.png");
        
        Button_SetOnClick(button, onClick, (void*)i);
        Sprite_SetRectangle(&sprites[i], (SDL_Rect){5+i, 10+i, 100+i, 100+i});
    
    }

    int running = 1;
    SDL_Event event;

    while (running) {
        Renderer_Clear(sprites, total_button);
        Renderer_Sprite_Copy(sprites, total_button);
        Renderer_Present(sprites, total_button);

        //SDL_RenderPresent(window->renderer);
        //SDL_RenderClear(window->renderer);
        //SDL_RenderCopy(window->renderer, window->texture, NULL, NULL);

     
    }

    //Button_Destroy(button1);
    //Window_Destroy(window);
    //SDL_Quit();

    return 0;
}