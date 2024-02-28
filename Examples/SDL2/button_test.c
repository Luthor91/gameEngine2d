//  gcc -I/usr/include/SDL2 -o button_test Examples/SDL2/button_test.c  Core/Graphics/src/button.c Core/Graphics/src/window.c Core/Graphics/src/sprite.c -lSDL2 -lSDL2_image -lm && ./button_test

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../Core/Graphics/include/window.h"
#include "../../Core/Graphics/include/button.h"
#include "../../Core/Graphics/include/sprite.h"

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

    Button* button = Button_Create(window->renderer, 50, 50, 100, 100, NULL, NULL);

    Button_SetSprite(button, window->renderer, "Assets/Image/button2.png");
    Button_SetOnClick(button, onClick, (void*)42);
    Sprite_SetRect(button->sprite, button->rect);

    int running = 1;
    SDL_Event event;

    while (running) {
        
        Window_Render(window);
        Button_Render(button);
        Sprite_Render(button->sprite);
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (Button_IsPressed(button, event.button.x, event.button.y)) {
                        running = 0;
                    }
            }
        }

        
    }

    //Button_Destroy(button);
    //Window_Destroy(window);
    //SDL_Quit();

    return 0;
}