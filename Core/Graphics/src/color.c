#include "../include/color.h"

// Fonction pour convertir Color en SDL_Color
SDL_Color Color_GetSDL(Color color) {
    SDL_Color sdl_color;
    sdl_color.r = color.r;
    sdl_color.g = color.g;
    sdl_color.b = color.b;
    sdl_color.a = color.a;
    return sdl_color;
}