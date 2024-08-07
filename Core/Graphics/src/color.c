#include "../include/color.h"

Color* Color_Init(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    Color* color = malloc(sizeof(Color));

    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;

    return color;
}

SDL_Color Color_GetSDL(Color color) {
    SDL_Color sdl_color;
    sdl_color.r = color.r;
    sdl_color.g = color.g;
    sdl_color.b = color.b;
    sdl_color.a = color.a;
    return sdl_color;
}