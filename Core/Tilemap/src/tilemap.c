#include "../include/tilemap.h"

Tilemap* Tilemap_Init(int rows, int columns, Size2D tile_size, Tile** tiles) {
    // Allocation mémoire pour le tilemap
    Tilemap* tilemap = (Tilemap*)malloc(sizeof(Tilemap));
    if (!tilemap) {
        return NULL; // Échec de l'allocation mémoire
    }

    // Initialisation des membres de la structure
    tilemap->rows = rows;
    tilemap->columns = columns;
    tilemap->tile_size = tile_size;
    tilemap->tiles = tiles;
    
    // Allocation mémoire pour la matrice de disposition des tuiles
    tilemap->map = (int*)malloc(rows * columns * sizeof(int));
    if (!tilemap->map) {
        free(tilemap);
        return NULL; // Échec de l'allocation mémoire
    }

    // Initialisation de la matrice avec des valeurs par défaut (par exemple, 0)
    for (int i = 0; i < rows * columns; i++) {
        tilemap->map[i] = 0;
    }

    return tilemap;
}