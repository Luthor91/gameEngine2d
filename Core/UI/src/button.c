#include "../include/button.h"

// Fonction pour créer un bouton
Button* Button_Create(int x, int y, int width, int height) {
    Button* button = (Button*) malloc(sizeof(Button));
    if (!button) {
        fprintf(stderr, "Button_Create: %s\n", IMG_GetError());
        return NULL;
    }

    button->aspect->bounds->x = x;
    button->aspect->bounds->y = y;
    button->aspect->bounds->w = width;
    button->aspect->bounds->h = height;
    button->pressed = 0;

    return button;
}

// Fonction pour créer un bouton
Button* Button_Init(Aspect* aspect, Sprite* sprite, void (*on_click)(void*), void* data) {
    Button* button = (Button*) malloc(sizeof(Button));
    if (!button) {
        fprintf(stderr, "Button_Init: %s\n", IMG_GetError());
        return NULL;
    }

    if (!sprite) {
        fprintf(stderr, "Button_Init: Sprite invalide\n");
        return NULL;
    }


    button->aspect = aspect;
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


    button->aspect = sprite->aspect;
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
    button->aspect->bounds->x = x;
    button->aspect->bounds->y = y;
    return 1;
}

int Button_SetSize(Button* button, int width, int height) {
    button->aspect->bounds->w = width;
    button->aspect->bounds->h = height;

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

int Button_SyncAspectWithSprite(Button* button) {

    button->aspect = button->sprite->aspect;
    return 1;
}

// Fonction pour vérifier si un bouton est pressé
int Button_IsPressed(Button* button, int x, int y) {

    if (x >= button->aspect->bounds->x && x <= button->aspect->bounds->x + button->aspect->bounds->w && y >= button->aspect->bounds->y && y <= button->aspect->bounds->y + button->aspect->bounds->h) {

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