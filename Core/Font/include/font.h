#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL_ttf.h>
#include "../../Graphics/include/color.h"

#define DEFAULT_FONT_SIZE 11 

/**
 * Représente une police de caractères pour le rendu de texte avec SDL_ttf.
 */
typedef struct Font {
    TTF_Font* sdl_font; ///< Police de caractères SDL_ttf associée à la structure.
    Color* color; ///< Couleur du texte à utiliser lors du rendu.
    char* path; ///< Chemin vers le fichier de police (fichier .ttf).
    int size; ///< Taille de la police.
} Font;

/**
 * Initialise le module SDL_ttf pour le rendu de texte.
 *
 * @return 1 si l'initialisation est réussie, sinon 0 en cas d'échec.
 */
int Font_Start();

Font* Font_SetSize(Font* font, int size);

/**
 * Crée et initialise une nouvelle police de caractères.
 *
 * @param color La couleur du texte à utiliser avec la police.
 * @param path Le chemin vers le fichier de police (.ttf) à charger.
 * @param size La taille de la police en points.
 * @return Un pointeur vers la nouvelle police de caractères initialisée, ou NULL en cas d'erreur.
 */
Font* Font_Init(Color* color, char* path, int size);

#endif // FONT_H
