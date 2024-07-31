#include "../include/window.h"

Window* Window_Init(char* title, Transform* transform, char* background_path) {
    if (background_path == NULL) {
        fprintf(stderr, "Window_Init: Sprite path is invalid, default value used\n");
        background_path = "Assets/Default/DefaultWindow.png";
    }

    if (title == NULL) {
        fprintf(stderr, "Window_Init: title invalid, default value used\n");
        title = "Default Title";
    }

    if (transform == NULL) {
        fprintf(stderr, "Window_Init: transform invalid, default value used\n");
        transform = Transform_Init(NULL, &(Size2D){DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}, NULL, 0, 0);
    }

    if (transform->scale <= 0.0) {
        transform->scale = 1.0;
    }
    Window* window = (Window*)malloc(sizeof(Window));
    if (!window) {
        fprintf(stderr, "Window_Init: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Window* sdl_window = SDL_CreateWindow(
        title,
        (int)transform->position->x,
        (int)transform->position->y,
        (int)(transform->size->width * transform->scale),
        (int)(transform->size->height * transform->scale),
        SDL_WINDOW_SHOWN
    );
    if (!sdl_window) {
        fprintf(stderr, "Window_Init: %s\n", SDL_GetError());
        free(window);
        return NULL;
    }

    window->sdl_window = sdl_window;
    window->transform = transform;

    SDL_Renderer* renderer = SDL_CreateRenderer(window->sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "Window_Init: %s\n", SDL_GetError());
        SDL_DestroyWindow(window->sdl_window);
        free(window);
        return NULL;
    }

    window->renderer = renderer;

    SDL_Renderer_Add(window->renderer);

    window->texture = Texture_Init(window->renderer, background_path);
    if (!window->texture) {
        fprintf(stderr, "Window_Init: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window->sdl_window);
        free(window);
        return NULL;
    }

    window->texture->size = transform->size;

    return window;
}

int Window_SetIcon(Window* window, const char* filename) {
    SDL_Surface* icon = SDL_LoadBMP(filename);
    if (!icon) {
        return 0;
    }

    SDL_SetWindowIcon(window->sdl_window, icon);
    SDL_FreeSurface(icon);

    return 1;
}

Size2D* Window_GetSize(Window* window) {
    return window->texture->size;
}

void Window_Destroy(Window* window) {
    if (window) {
        if (window->texture) {
            SDL_DestroyTexture(window->texture->sdl_texture);
            free(window->texture);
        }
        if (window->renderer) {
            SDL_DestroyRenderer(window->renderer);
        }
        if (window->sdl_window) {
            SDL_DestroyWindow(window->sdl_window);
        }
        free(window);
    }
}
