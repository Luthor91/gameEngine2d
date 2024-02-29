#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/button.h"

// Fonction pour créer un bouton
Button* Button_Create(int x, int y, int width, int height) {
    Button* button = (Button*) malloc(sizeof(Button));
    if (!button) {
        fprintf(stderr, "Button_Create: %s\n", IMG_GetError());
        return NULL;
    }

    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = width;
    button->rect.h = height;
    button->pressed = 0;

    return button;
}

// Fonction pour détruire un bouton
void Button_Destroy(Button* button) {
    if (!button) {
        return;
    }

    Sprite_Destroy(button->sprite);
    
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

    return 1;
}

int Button_SetSprite(Button* button, SDL_Renderer* renderer, const char* path) {

    button->sprite = Sprite_Create(renderer, path);
    
    return 1;
}

int Button_SetOnClick(Button* button, void (*on_click)(void*), void* data) {
    button->on_click = on_click;
    button->data = data;
    return 1;
}

int Button_SyncRectWithSprite(Button* button) {

    button->rect = button->sprite->rect;
    return 1;
}

// Fonction pour vérifier si un bouton est pressé
int Button_IsPressed(Button* button, int x, int y) {

    if (x >= button->rect.x && x <= button->rect.x + button->rect.w && y >= button->rect.y && y <= button->rect.y + button->rect.h) {

        if (button->pressed) {
            return 0;
        }

        button->pressed = 1;

        if (button->on_click) {
            button->on_click(button->data);
        }

        return 1;
    }

    button->pressed = 0;

    return 0;
}

void Button_Render(Button* button) {
    Sprite_Render(button->sprite);
}
