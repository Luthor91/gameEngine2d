#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include "../../Graphics/include/texture.h"
#include "../../Spatial/include/transform.h"

typedef struct Window {
    SDL_Window* sdl_window;
    SDL_Renderer* renderer;
    Transform* transform;
    Texture* texture;
} Window;

Window* Window_Init(const char* title, Transform* transform, const char* sprite_path);
int Window_SetIcon(Window* window, const char* filename);
void Window_Destroy(Window* window);


#endif // WINDOW_H