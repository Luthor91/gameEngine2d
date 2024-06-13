#ifndef TILEMAP_H
#define TILEMAP_H

#include "../../Graphics/include/texture.h"
#include "../../Spatial/include/size2d.h"
#include "../../Spatial/include/point2d.h"

typedef struct Tile {
    int id; // Identifiant unique de la tuile
    Texture* texture; // Texture associée à la tuile
    Point2D* position; // La position de la tuile dans la texture
    Size2D* size; // La taille de la tuile
} Tile;

typedef struct Tilemap {
    Tile** tiles; // Tableau de pointeurs vers des tuiles
    int rows; // Nombre de lignes dans la grille
    int columns; // Nombre de colonnes dans la grille
    Size2D* tile_size; // Taille de chaque tuile
    int* map; // Matrice représentant la disposition des tuiles (par leurs ID)
} Tilemap;

// Fonction pour initialiser un tilemap
Tilemap* Tilemap_Init(SDL_Renderer* renderer, int rows, int columns, Size2D* tile_size, Texture* texture);


#endif // TILEMAP_H