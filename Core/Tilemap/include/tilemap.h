#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL2/SDL.h>

#include "sprite.h"

typedef struct Tile {
    int id;             // Identifiant unique du tile
    SDL_Rect* rect;      // Rectangle délimitant le tile dans le sprite
} Tile;

typedef struct Tilemap {
    SDL_Texture* texture;   // Texture contenant les tiles
    int tile_width;         // Largeur d'un tile en pixels
    int tile_height;        // Hauteur d'un tile en pixels
    int num_cols;           // Nombre de colonnes dans le tileset
    int num_rows;           // Nombre de lignes dans le tileset
    Tile** tiles;           // Tableau de tiles pour accéder aux informations de chaque tile
} Tilemap;

// Fonction pour initialiser un Tilemap à partir d'une texture
Tilemap* Tilemap_Init(Sprite* sprite, int tile_width, int tile_height);
void Tilemap_RenderTile(Tilemap* tilemap, SDL_Renderer* renderer, int id, int x, int y);
void Tilemap_Destroy(Tilemap* tilemap);

#endif // TILEMAP_H