#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/button.h"
#include "../include/sprite.h"

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

// Fonction pour créer un bouton
Button* Button_Init(int x, int y, int width, int height, Sprite* sprite, void (*on_click)(void*), void* data) {
    Button* button = (Button*) malloc(sizeof(Button));
    if (!button) {
        fprintf(stderr, "Button_Init: %s\n", IMG_GetError());
        return NULL;
    }

    if (!sprite) {
        fprintf(stderr, "Button_Init: Sprite invalide\n");
        return NULL;
    }


    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = width;
    button->rect.h = height;
    button->pressed = 0;
    button->sprite = sprite;
    button->data = data;
    button->on_click = on_click;

    return button;
}

Button* Button_InheritSprite(Sprite* sprite, void (*on_click)(void*), void* data) {
    Button* button = (Button*) malloc(sizeof(Button));
    if (!button) {
        fprintf(stderr, "Button_InheritsSprite: %s\n", IMG_GetError());
        return NULL;
    }

    if (!sprite) {
        fprintf(stderr, "Button_InheritsSprite: Sprite invalide\n");
        return NULL;
    }


    button->rect.x = sprite->rect.x;
    button->rect.y = sprite->rect.y;
    button->rect.w = sprite->rect.w;
    button->rect.h = sprite->rect.h;
    button->pressed = 0;
    button->sprite = sprite;
    button->data = data;
    button->on_click = on_click;

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
    button->rect.w = width;
    button->rect.h = height;

    return 1;
}

int Button_SetSprite(Button* button, Sprite* sprite) {

    button->sprite = sprite;
    
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