//  gcc -I/usr/include/SDL2 -o window_test window_test.c ../../Core/Graphics/src/window.c -lSDL2 -lSDL2_image -lm && ./window_test

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../Core/Graphics/include/window.h"


int main(int argc, char* argv[]) {

    Window* window = Window_Create("Window Test", 640, 480 );
    Window_LoadTexture(window, "../../Assets/Image/background1.jpg");
    
    while(1) {
        Window_Render(window);
    }
    
    Window_Destroy(window);
    SDL_Quit();

    return 0;

}