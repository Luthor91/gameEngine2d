#include "../include/tilemap.h"

// Fonction pour initialiser un Tilemap à partir d'une texture
Tilemap* Tilemap_Init(Sprite* sprite, int tile_width, int tile_height) {

    SDL_Texture* texture = sprite->texture;
    if (!texture) {
        printf("Tilemap_Init: Erreur lors de la création de la texture\n");
        return NULL;
    }
    
    int num_cols = sprite->aspect->bounds->w / tile_width;
    int num_rows = sprite->aspect->bounds->h / tile_height;

    // Allocation de mémoire pour le Tilemap
    Tilemap* tilemap = (Tilemap*)malloc(sizeof(Tilemap));
    if (!tilemap) {
        printf("Tilemap_Init: Erreur lors de l'allocation de mémoire pour le Tilemap\n");
        SDL_DestroyTexture(texture);
        return NULL;      
    }

    // Initialisation des membres du Tilemap
    tilemap->texture = texture;
    tilemap->tile_width = tile_width;
    tilemap->tile_height = tile_height;
    tilemap->num_cols = num_cols;
    tilemap->num_rows = num_rows;

    // Allocation de mémoire pour le tableau de tiles
    tilemap->tiles = (Tile**)malloc(num_rows * num_cols * sizeof(Tile*));
    if (!tilemap->tiles) {
        printf("Tilemap_Init: Erreur lors de l'allocation de mémoire pour le tableau de tiles\n");
        SDL_DestroyTexture(texture);
        free(tilemap);
        return NULL;
    }

    // Découpage de la texture en tiles
    for (int i = 0; i < num_rows; i++) {
        tilemap->tiles[i] = (Tile*)malloc(num_cols * sizeof(Tile));
        if (!tilemap->tiles[i]) {
            printf("Tilemap_Init: Erreur lors de l'allocation de mémoire pour les tiles de la ligne %d\n", i);
            Tilemap_Destroy(tilemap);
            return NULL;
        }

        for (int j = 0; j < num_cols; j++) {
            // Allocation de mémoire pour chaque tile
            Tile* tile = malloc(sizeof(Tile));
            if (!tile) {
                printf("Tilemap_Init: Erreur lors de l'allocation de mémoire pour la tile (%d, %d)\n", i, j);
                Tilemap_Destroy(tilemap);
                return NULL;
            }
            
            // Allocation de mémoire pour le rectangle de la tile
            tile->rect = malloc(sizeof(SDL_Rect));
            if (!tile->rect) {
                printf("Tilemap_Init: Erreur lors de l'allocation de mémoire pour le rectangle de la tile (%d, %d)\n", i, j);
                free(tile);
                Tilemap_Destroy(tilemap);
                return NULL;
            }

            tile->id = i * num_cols + j;
            tile->rect->x = j * tile_width;
            tile->rect->y = i * tile_height;
            tile->rect->w = tile_width;
            tile->rect->h = tile_height;
            tilemap->tiles[i][j] = *tile;
        }
    }
    return tilemap;
}

// Fonction pour rendre une seule tile du Tilemap

void Tilemap_RenderTile(Tilemap* tilemap, SDL_Renderer* renderer, int id, int x, int y) {
    
    if (!tilemap || !renderer ) {
        printf("Tilemap_RenderTile: Erreur fatale, tilemap ou renderer erroné\n");
        return;
    }

    if (id < 0 || id >= tilemap->num_cols * tilemap->num_rows) {
        printf("Tilemap_RenderTile: Erreur, id : %d doit être compris entre 0 et %d\n", id, tilemap->num_cols * tilemap->num_rows);
        return;
    }

    // Calcul de l'indice de colonne et de ligne à partir de l'ID
    int col = id % tilemap->num_cols;
    int row = id / tilemap->num_cols;

    // Récupération de la texture de la tilemap
    if (!tilemap->texture) {
        printf("Erreur : texture non définie\n");
        return;
    }

    // Calcul des coordonnées de la tile dans la texture
    SDL_Rect src_rect = {
        .x = col * tilemap->tile_width,
        .y = row * tilemap->tile_height,
        .w = tilemap->tile_width,
        .h = tilemap->tile_height
    };

    SDL_Rect dest_rect = {
        .x = x,
        .y = y,
        .w = tilemap->tile_width,
        .h = tilemap->tile_height
    };

    SDL_RenderCopy(renderer, tilemap->texture, &src_rect, &dest_rect);
}

// Fonction pour libérer la mémoire allouée pour un Tilemap
void Tilemap_Destroy(Tilemap* tilemap) {
    if (tilemap) {
        if (tilemap->tiles) {
            for (int i = 0; i < tilemap->num_rows; i++) {
                free(tilemap->tiles[i]);
            }
            free(tilemap->tiles);
        }
        SDL_DestroyTexture(tilemap->texture);
        free(tilemap);
    }
}