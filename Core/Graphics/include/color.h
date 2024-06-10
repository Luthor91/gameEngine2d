#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>

typedef struct Color {
    Uint8 r, g, b, a;
} Color;

// Définition de quelques couleurs courantes sous forme de constantes
#define COLOR_BLACK     (Color){0, 0, 0, 255}
#define COLOR_WHITE     (Color){255, 255, 255, 255}
#define COLOR_RED       (Color){255, 0, 0, 255}
#define COLOR_GREEN     (Color){0, 255, 0, 255}
#define COLOR_BLUE      (Color){0, 0, 255, 255}
#define COLOR_YELLOW    (Color){255, 255, 0, 255}
#define COLOR_CYAN      (Color){0, 255, 255, 255}
#define COLOR_MAGENTA   (Color){255, 0, 255, 255}

#endif