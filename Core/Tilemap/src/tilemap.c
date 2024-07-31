#include "../include/tilemap.h"

Tilemap* Tilemap_Init(SDL_Renderer* renderer, int rows, int columns, Size2D* tile_size, Texture* texture) {
    Tilemap* tilemap = (Tilemap*)malloc(sizeof(Tilemap));
    if (!tilemap) {
        return NULL;
    }

    tilemap->rows = rows;
    tilemap->columns = columns;
    tilemap->tile_size = tile_size;
    
    tilemap->tiles = (Tile**)malloc(rows * columns * sizeof(Tile*));
    if (!tilemap->tiles) {
        free(tilemap);
        return NULL;
    }

    tilemap->map = (int*)malloc(rows * columns * sizeof(int));
    if (!tilemap->map) {
        free(tilemap->tiles);
        free(tilemap);
        return NULL;
    }

    int tile_id = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            Tile* tile = (Tile*)malloc(sizeof(Tile));
            if (!tile) {
                for (int i = 0; i < tile_id; i++) {
                    free(tilemap->tiles[i]->position);
                    SDL_DestroyTexture(tilemap->tiles[i]->texture->sdl_texture);
                    free(tilemap->tiles[i]->texture->size);
                    free(tilemap->tiles[i]->texture);
                    free(tilemap->tiles[i]);
                }
                free(tilemap->tiles);
                free(tilemap->map);
                free(tilemap);
                return NULL;
            }

            Point2D* pos = Point2D_Init(col * tilemap->tile_size->width, row * tilemap->tile_size->height);
            
            tile->texture = Texture_Crop(texture, renderer, pos, tilemap->tile_size);

            if (!tile->texture) {
                free(tile->position);
                free(tile);
                for (int i = 0; i < tile_id; i++) {
                    free(tilemap->tiles[i]->position);
                    SDL_DestroyTexture(tilemap->tiles[i]->texture->sdl_texture);
                    free(tilemap->tiles[i]->texture->size);
                    free(tilemap->tiles[i]->texture);
                    free(tilemap->tiles[i]);
                }
                free(tilemap->tiles);
                free(tilemap->map);
                free(tilemap);
                return NULL;
            }

            tile->id = tile_id;
            tile->position = pos;
            tile->size = tile_size;

            tilemap->tiles[tile_id] = tile;
            tilemap->map[row * columns + col] = tile_id;
            tile_id++;
        }
    }

    return tilemap;
}
