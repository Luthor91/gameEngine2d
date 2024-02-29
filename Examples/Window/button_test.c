//  gcc -I/usr/include/SDL2 -o Examples/SDL2/button_test button_test.c  Core/Graphics/src/button.c Core/Graphics/src/window.c Core/Graphics/src/renderer.c -lSDL2 -lSDL2_image -lm && ./button_test

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../Core/Graphics/include/window.h"
#include "../../Core/Graphics/include/button.h"

int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    Window* window = Window_Create("Window Test", 640, 480 );
    Window_LoadTexture(window, "../../Assets/Image/background1.jpg");

    Button* button = Button_Create(window->renderer, 100, 100, 300, 100, NULL, NULL);
    Button_LoadTexture(button, "../../Assets/Image/button1.png");

    int running = 1;
    SDL_Event event;

    while (running) {
        Button_Render(button);
        Window_Render(window);
        
        
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (Button_IsPressed(button, event.button.x, event.button.y)) {
                        running = 0;
                        printf("Button pressed");
                    }
                    break;
            }
        }

        
    }

    Button_Destroy(button);
    Window_Destroy(window);
    SDL_Quit();

    return 0;
}