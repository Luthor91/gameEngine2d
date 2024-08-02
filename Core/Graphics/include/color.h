#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>

/**
 * Définition de quelques couleurs courantes sous forme de constantes.
 */
#define COLOR_BLACK     (Color){0, 0, 0, 255}      ///< Noir, avec une opacité complète.
#define COLOR_WHITE     (Color){255, 255, 255, 255} ///< Blanc, avec une opacité complète.
#define COLOR_RED       (Color){255, 0, 0, 255}    ///< Rouge, avec une opacité complète.
#define COLOR_GREEN     (Color){0, 255, 0, 255}    ///< Vert, avec une opacité complète.
#define COLOR_BLUE      (Color){0, 0, 255, 255}    ///< Bleu, avec une opacité complète.
#define COLOR_YELLOW    (Color){255, 255, 0, 255}  ///< Jaune, avec une opacité complète.
#define COLOR_CYAN      (Color){0, 255, 255, 255}  ///< Cyan, avec une opacité complète.
#define COLOR_MAGENTA   (Color){255, 0, 255, 255}  ///< Magenta, avec une opacité complète.

/**
 * Représente une couleur en termes de composantes rouge, verte, bleue et alpha.
 */
typedef struct Color {
    Uint8 r; ///< Composante rouge de la couleur (0 à 255).
    Uint8 g; ///< Composante verte de la couleur (0 à 255).
    Uint8 b; ///< Composante bleue de la couleur (0 à 255).
    Uint8 a; ///< Composante alpha (opacité) de la couleur (0 à 255).
} Color;

/**
 * Initialise une couleur avec les composantes RGBA spécifiées.
 * 
 * Cette fonction crée une nouvelle structure `Color` et initialise ses composantes 
 * rouge (R), verte (G), bleue (B) et alpha (A) avec les valeurs fournies.
 *
 * @param r La composante rouge de la couleur (0 à 255).
 * @param g La composante verte de la couleur (0 à 255).
 * @param b La composante bleue de la couleur (0 à 255).
 * @param a La composante alpha (opacité) de la couleur (0 à 255).
 * @return Un pointeur vers la structure `Color` nouvellement créée et initialisée.
 */
Color* Color_Init(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

/**
 * Convertit une couleur définie en `Color` vers une couleur SDL2 (`SDL_Color`).
 *
 * @param color La couleur à convertir, représentée par une structure `Color`.
 * @return La couleur SDL2 correspondante sous la forme d'une structure `SDL_Color`.
 */
SDL_Color Color_GetSDL(Color color);

#endif // COLOR_H
