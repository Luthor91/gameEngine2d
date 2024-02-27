#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/button.h"

// Fonction pour créer un bouton
Button* Button_Create(SDL_Renderer* renderer, int x, int y, int w, int h, void (*on_click)(void*), void* data) {
    Button* button = (Button*) malloc(sizeof(Button));
    if (!button) {
        fprintf(stderr, "Button_Create: %s\n", IMG_GetError());
        return NULL;
    }

    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = w;
    button->rect.h = h;
    button->pressed = 0;
    button->on_click = on_click;
    button->data = data;

    // Initialiser les attributs renderer, texture, on_click et data
    button->renderer = renderer;
    //button->texture = IMG_LoadTexture(button->renderer, "Assets/Image/button1.png");
    button->on_click = on_click;
    button->data = data;

    return button;
}

// Fonction pour détruire un bouton
void Button_Destroy(Button* button) {
    if (!button) {
        return;
    }

    SDL_DestroyTexture(button->texture);
    SDL_DestroyRenderer(button->renderer);
    
    free(button);
}

int Button_SetPosition(Button* button, int x, int y) {
    // Set the button's position on the screen
    button->rect.x = x;
    button->rect.y = y;
    return 1;
}

int Button_SetSize(Button* button, int width, int height) {
    // Set the button's size and scale
    button->rect.w = width;
    button->rect.h = height;

    // Set the renderer's size and scale
    SDL_RenderSetLogicalSize(button->renderer, width, height);

    return 1;
}

int Button_LoadTexture(Button* button, const char* path)
{
    // Load the image
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (!loadedSurface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return 0;
    }

    // Create a new texture
    button->texture = SDL_CreateTexture(button->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, loadedSurface->w, loadedSurface->h);
    if (!button->texture) {
        printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        return 0;
    }

    // Blit the surface onto the texture
    if (SDL_BlitSurface(loadedSurface, NULL, button->texture, NULL) < 0) {
        printf("Unable to blit surface to texture! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    // Get the width and height of the image
    button->rect.w = loadedSurface->w;
    button->rect.h = loadedSurface->h;

    return 1;
}
// Fonction pour vérifier si un bouton est pressé
int Button_IsPressed(Button* button, int x, int y) {
    // Vérifier si la souris est sur le bouton
    if (x >= button->rect.x && x <= button->rect.x + button->rect.w && y >= button->rect.y && y <= button->rect.y + button->rect.h) {
        // Si le bouton est déjà pressé, ne rien faire
        if (button->pressed) {
            return 0;
        }

        // Définir l'état du bouton comme pressé
        button->pressed = 1;

        // Appeler la fonction de rappel pour le clic
        if (button->on_click) {
            button->on_click(button->data);
        }

        return 1;
    }

    // Si le bouton n'est pas pressé, définir l'état du bouton comme non pressé
    button->pressed = 0;

    return 0;
}

// Fonction pour dessiner un bouton
void Button_Render(Button* button) {
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = button->rect.w;
    srcRect.h = button->rect.h;

    SDL_RenderClear(button->renderer);
    SDL_RenderCopy(button->renderer, button->texture, &srcRect, &button->rect);  
    SDL_RenderPresent(button->renderer);
}
