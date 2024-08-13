
#ifndef TEXTURE_UTILS_H
#define TEXTURE_UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define COLOR_BLACK    (SDL_Color){0, 0, 0, 255}
#define COLOR_WHITE    (SDL_Color){255, 255, 255, 255}
#define COLOR_RED      (SDL_Color){255, 0, 0, 255}
#define COLOR_GREEN    (SDL_Color){0, 255, 0, 255}
#define COLOR_BLUE     (SDL_Color){0, 0, 255, 255}
#define COLOR_YELLOW   (SDL_Color){255, 255, 0, 255}
#define COLOR_CYAN     (SDL_Color){0, 255, 255, 255}
#define COLOR_MAGENTA  (SDL_Color){255, 0, 255, 255}
#define COLOR_GRAY     (SDL_Color){128, 128, 128, 255}
#define COLOR_ORANGE   (SDL_Color){255, 165, 0, 255}
#define COLOR_PURPLE   (SDL_Color){128, 0, 128, 255}
#define COLOR_BROWN    (SDL_Color){165, 42, 42, 255}
#define COLOR_PINK     (SDL_Color){255, 192, 203, 255}

SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);
SDL_Texture* loadColor(SDL_Renderer* renderer, SDL_Color color, int width, int height);

#endif

