#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include "../../Spatial/include/size2d.h"

/**
 * 
 * texture : texture SDL
 * size : taille de la texture source
 * */ 
typedef struct Texture {
    SDL_Texture* sdl_texture;
    Size2D* size;
} Texture;

// Déclaration de la fonction d'initialisation de la texture
Texture* Texture_Init(SDL_Renderer* renderer, const char* file);

#endif // TEXTURE_H
