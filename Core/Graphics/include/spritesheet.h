#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "sprite.h"
#include "../../Spatial/include/size2d.h"

/**
 * Représente une feuille de sprites, qui est une texture contenant plusieurs sprites.
 */
typedef struct SpriteSheet {
    Sprite** sprites; ///< Tableau de pointeurs vers les sprites individuels extraits de la feuille.
    Texture* texture; ///< Texture contenant l'ensemble des sprites de la feuille.
    Size2D* tile_size; ///< Taille d'une tuile dans la feuille (largeur et hauteur d'un sprite individuel).
    int max_frame; ///< Nombre maximal de frames dans la feuille de sprites.
} SpriteSheet;

/**
 * Initialise une nouvelle feuille de sprites.
 *
 * @param renderer Le renderer SDL2 utilisé pour dessiner les sprites de la feuille.
 * @param texture La texture contenant l'ensemble des sprites pour la feuille.
 * @param tile_size La taille d'une tuile (largeur et hauteur) dans la feuille de sprites.
 * @param max_frame Le nombre maximal de frames (sprites) dans la feuille.
 * @return Un pointeur vers la nouvelle feuille de sprites initialisée, ou NULL en cas d'erreur.
 */
SpriteSheet* SpriteSheet_Init(SDL_Renderer* renderer, Texture* texture, Size2D tile_size, int max_frame);

#endif // SPRITESHEET_H
