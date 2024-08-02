#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "../../Renderer/include/sdl_renderer.h"
#include "../../Spatial/include/size2d.h"
#include "../../Spatial/include/point2d.h"
#include "color.h"

/**
 * Représente une texture SDL, avec ses informations associées.
 */
typedef struct Texture {
    SDL_Texture* sdl_texture; ///< Texture SDL associée à la structure.
    Size2D* size; ///< Taille de la texture (largeur et hauteur).
} Texture;

/**
 * Initialise une nouvelle texture à partir d'un fichier image.
 *
 * @param renderer Le renderer SDL2 utilisé pour créer la texture.
 * @param file Le chemin du fichier image à charger comme texture.
 * @return Un pointeur vers la nouvelle texture initialisée, ou NULL en cas d'erreur.
 */
Texture* Texture_Init(SDL_Renderer* renderer, char* file);

/**
 * @brief Initialise une texture d'une couleur unie.
 * 
 * @param renderer Le renderer SDL utilisé pour créer la texture.
 * @param color La couleur unie de la texture.
 * @param width Largeur de la texture.
 * @param height Hauteur de la texture.
 * @return Pointeur vers la texture initialisée, ou NULL en cas d'erreur.
 */
Texture* Texture_Init_Color(SDL_Renderer* renderer, Color* color, Size2D* size);

/**
 * Crée une nouvelle texture en découpant une partie d'une texture existante.
 *
 * @param original La texture d'origine à découper.
 * @param renderer Le renderer SDL2 utilisé pour créer la nouvelle texture.
 * @param pos La position du coin supérieur gauche de la région à découper dans la texture d'origine.
 * @param size La taille de la région à découper (largeur et hauteur).
 * @return Un pointeur vers la nouvelle texture découpée, ou NULL en cas d'erreur.
 */
Texture* Texture_Crop(Texture* original, SDL_Renderer* renderer, Point2D* pos, Size2D* size);

void Texture_Destroy(Texture* texture);

#endif // TEXTURE_H
