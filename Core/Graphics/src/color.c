#include "../include/color.h"

Color* Color_Init(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    Color* color = malloc(sizeof(Color));

    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;

    return color;
}

// Fonction de parsing pour les couleurs
int Color_Parsing(Color* color, const char* str) {
    if (strcmp(str, "RED") == 0) {
        *color = COLOR_RED;
    } else if (strcmp(str, "GREEN") == 0) {
        *color = COLOR_GREEN;
    } else if (strcmp(str, "BLUE") == 0) {
        *color = COLOR_BLUE;
    } else if (strcmp(str, "WHITE") == 0) {
        *color = COLOR_WHITE;
    } else if (strcmp(str, "BLACK") == 0) {
        *color = COLOR_BLACK;
    } else if (strcmp(str, "YELLOW") == 0) {
        *color = COLOR_YELLOW;
    } else if (strcmp(str, "CYAN") == 0) {
        *color = COLOR_CYAN;
    } else if (strcmp(str, "MAGENTA") == 0) {
        *color = COLOR_MAGENTA;
    } else if (sscanf(str, "%hhd,%hhd,%hhd,%hhd", &color->r, &color->g, &color->b, &color->a) == 4) {
        return 1; // Successfully parsed RGBA color
    } else {
        return 0; // Invalid color format
    }
    return 1;
}

SDL_Color Color_GetSDL(Color color) {
    SDL_Color sdl_color;
    sdl_color.r = color.r;
    sdl_color.g = color.g;
    sdl_color.b = color.b;
    sdl_color.a = color.a;
    return sdl_color;
}