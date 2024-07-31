#ifndef TILEMAP_H
#define TILEMAP_H

#include "../../Graphics/include/texture.h"
#include "../../Spatial/include/size2d.h"
#include "../../Spatial/include/point2d.h"

/**
 * @brief Structure représentant une tuile dans le tilemap.
 */
typedef struct Tile {
    int id; ///< Identifiant unique de la tuile.
    Texture* texture; ///< Texture associée à la tuile.
    Point2D* position; ///< Position de la tuile dans la texture (ex. coordonnées de la région à afficher).
    Size2D* size; ///< Taille de la tuile.
} Tile;

/**
 * @brief Structure représentant un tilemap.
 */
typedef struct Tilemap {
    Tile** tiles; ///< Tableau de pointeurs vers des tuiles, représentant toutes les tuiles disponibles dans le tilemap.
    int rows; ///< Nombre de lignes dans la grille de tuiles.
    int columns; ///< Nombre de colonnes dans la grille de tuiles.
    Size2D* tile_size; ///< Taille de chaque tuile dans le tilemap.
    int* map; ///< Matrice représentant la disposition des tuiles dans le tilemap, stocke les IDs des tuiles pour chaque position.
} Tilemap;

/**
 * @brief Initialise un nouveau tilemap avec les paramètres spécifiés.
 * 
 * @param renderer Pointeur vers le renderer SDL utilisé pour dessiner les tuiles.
 * @param rows Nombre de lignes dans le tilemap.
 * @param columns Nombre de colonnes dans le tilemap.
 * @param tile_size Pointeur vers une structure Size2D définissant la taille de chaque tuile.
 * @param texture Pointeur vers la texture associée au tilemap.
 * @return Un pointeur vers le tilemap nouvellement créé, ou NULL en cas d'échec.
 */
Tilemap* Tilemap_Init(SDL_Renderer* renderer, int rows, int columns, Size2D* tile_size, Texture* texture);

#endif // TILEMAP_H
