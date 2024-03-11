#include "../include/button.h"

// Fonction pour créer un bouton
Button* Button_Create(int x, int y, int width, int height) {
    Button* button = (Button*) malloc(sizeof(Button));
    if (!button) {
        fprintf(stderr, "Button_Create: %s\n", IMG_GetError());
        return NULL;
    }

    button->transform->bounds->x = x;
    button->transform->bounds->y = y;
    button->transform->bounds->w = width;
    button->transform->bounds->h = height;
    button->pressed = 0;

    return button;
}

// Fonction pour créer un bouton
Button* Button_Init(Transform* transform, Sprite* sprite, void (*on_click)(void*), void* data) {
    Button* button = (Button*) malloc(sizeof(Button));
    if (!button) {
        fprintf(stderr, "Button_Init: %s\n", IMG_GetError());
        return NULL;
    }

    if (!sprite) {
        fprintf(stderr, "Button_Init: Sprite invalide\n");
        return NULL;
    }


    button->transform = transform;
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


    button->transform = sprite->transform;
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
    button->transform->bounds->x = x;
    button->transform->bounds->y = y;
    return 1;
}

int Button_SetSize(Button* button, int width, int height) {
    button->transform->bounds->w = width;
    button->transform->bounds->h = height;

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

int Button_SyncTransformWithSprite(Button* button) {

    button->transform = button->sprite->transform;
    return 1;
}

// Fonction pour vérifier si un bouton est pressé
int Button_IsPressed(Button* button, int x, int y) {

    if (x >= button->transform->bounds->x && x <= button->transform->bounds->x + button->transform->bounds->w && y >= button->transform->bounds->y && y <= button->transform->bounds->y + button->transform->bounds->h) {

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