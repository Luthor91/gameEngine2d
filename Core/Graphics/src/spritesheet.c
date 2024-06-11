#include "../include/spritesheet.h"

// Fonction d'initialisation pour la structure SpriteSheet
SpriteSheet* SpriteSheet_Init(SDL_Renderer* renderer, Texture* texture, Size2D tile_size, int max_frame) {
    // Allocation de mémoire pour la structure SpriteSheet
    SpriteSheet* spritesheet = (SpriteSheet*)malloc(sizeof(SpriteSheet));
    if (spritesheet == NULL) {
        return NULL; // Retourner NULL en cas d'échec de l'allocation
    }

    // Initialisation de la texture
    spritesheet->texture = texture;
    
    // Initialisation de la taille des tuiles
    spritesheet->tile_size = (Size2D*)malloc(sizeof(Size2D));
    if (spritesheet->tile_size == NULL) {
        free(spritesheet);
        return NULL; // Retourner NULL en cas d'échec de l'allocation
    }
    spritesheet->tile_size->width = tile_size.width;
    spritesheet->tile_size->height = tile_size.height;

    // Initialisation du nombre maximum de frames
    spritesheet->max_frame = max_frame;

    // Allocation de mémoire pour le tableau de sprites
    spritesheet->sprites = (Sprite**)malloc(max_frame * sizeof(Sprite*));
    if (spritesheet->sprites == NULL) {
        free(spritesheet->tile_size);
        free(spritesheet);
        return NULL; // Retourner NULL en cas d'échec de l'allocation
    }

    // Initialisation des sprites à partir de la texture
    for (int i = 0; i < max_frame; i++) {
        spritesheet->sprites[i] = (Sprite*)malloc(sizeof(Sprite));
        if (spritesheet->sprites[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(spritesheet->sprites[j]);
            }
            free(spritesheet->sprites);
            free(spritesheet->tile_size);
            free(spritesheet);
            return NULL; // Retourner NULL en cas d'échec de l'allocation
        }

        // Calcul de la position de la tuile dans la texture
        int cols = texture->size->width / tile_size.width;
        int x = (i % cols) * tile_size.width;
        int y = (i / cols) * tile_size.height;

        // Initialisation de chaque sprite
        spritesheet->sprites[i]->texture = texture;
        spritesheet->sprites[i]->transform = (Transform*)malloc(sizeof(Transform));
        if (spritesheet->sprites[i]->transform == NULL) {
            for (int j = 0; j <= i; j++) {
                free(spritesheet->sprites[j]);
            }
            free(spritesheet->sprites);
            free(spritesheet->tile_size);
            free(spritesheet);
            return NULL; // Retourner NULL en cas d'échec de l'allocation
        }
        spritesheet->sprites[i]->transform->position = (Point2D*)malloc(sizeof(Point2D));
        spritesheet->sprites[i]->transform->size = (Size2D*)malloc(sizeof(Size2D));
        if (spritesheet->sprites[i]->transform->position == NULL || spritesheet->sprites[i]->transform->size == NULL) {
            for (int j = 0; j <= i; j++) {
                free(spritesheet->sprites[j]->transform->position);
                free(spritesheet->sprites[j]->transform->size);
                free(spritesheet->sprites[j]->transform);
                free(spritesheet->sprites[j]);
            }
            free(spritesheet->sprites);
            free(spritesheet->tile_size);
            free(spritesheet);
            return NULL; // Retourner NULL en cas d'échec de l'allocation
        }
        spritesheet->sprites[i]->transform->position->x = x;
        spritesheet->sprites[i]->transform->position->y = y;
        spritesheet->sprites[i]->transform->size->width = tile_size.width;
        spritesheet->sprites[i]->transform->size->height = tile_size.height;
    }

    return spritesheet;
}