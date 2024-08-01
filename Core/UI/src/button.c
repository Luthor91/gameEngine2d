#include "../include/button.h"

Button* Button_Init(Transform* transform, Texture* texture, void (*on_click)(void*), void* data) {

    if (texture == NULL) {
        fprintf(stderr, "Button_Init: texture invalid, default value used\n");
        texture = Texture_Init(NULL, "Assets/Default/DefaultButton.png");
    }

    if (transform == NULL) {
        fprintf(stderr, "Button_Init: transform invalid, default value used\n");
        transform = Transform_Init(NULL, &(Size2D){DEFAULT_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGHT}, NULL, 0, 0);
    }

    Button* button = (Button*)malloc(sizeof(Button));
    if (!button) {
        return NULL;
    }

    button->transform = transform;
    button->texture = texture;
    button->pressed = 0;  // Initialement, le bouton n'est pas pressé
    button->on_click = on_click;
    button->data = data;

    return button;
}

void Button_Set(Button* button, const char* params) {
    Object_Set(button, params, "Button");
}

void Button_Destroy(Button* button) {
    if (button) {
        free(button);
    }
}

int Button_SetOnClick(Button* button, void (*on_click)(void*), void* data) {
    if (!button) {
        return -1;  // Erreur: bouton non valide
    }

    button->on_click = on_click;
    button->data = data;
    return 0;  // Succès
}

void Button_SetPosition(Button* button, int x, int y) {

    if (x < 0) {
        x = button->transform->position->x;
    }

    if (y < 0) {
        y = button->transform->position->y;
    }
    
    button->transform->position->x = x;
    button->transform->position->y = y;

}

void Button_SetSize(Button* button, int width, int height) {

    if (width < 0) {
        width = button->transform->size->width;
    }

    if (height < 0) {
        height = button->transform->size->height;
    }
    
    button->transform->size->width = width;
    button->transform->size->height = height;

}