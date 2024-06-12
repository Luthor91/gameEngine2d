#include "../include/button.h"

// Initialise un bouton avec les paramètres spécifiés
Button* Button_Init(Transform* transform, Texture* texture, void (*on_click)(void*), void* data) {
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

// Détruit le bouton et libère la mémoire allouée
void Button_Destroy(Button* button) {
    if (button) {
        free(button);
    }
}

// Définir la fonction on_click et les données associées pour le bouton
int Button_SetOnClick(Button* button, void (*on_click)(void*), void* data) {
    if (!button) {
        return -1;  // Erreur: bouton non valide
    }

    button->on_click = on_click;
    button->data = data;
    return 0;  // Succès
}

// Vérifie si le bouton est pressé en fonction de la position donnée
int Button_IsPressed(Button* button, Point2D* position) {
    if (!button || !position) {
        return 0;  // Bouton non pressé
    }

    float x = position->x;
    float y = position->y;
    float btn_x = button->transform->position->x;
    float btn_y = button->transform->position->y;
    float btn_w = button->transform->size->width;
    float btn_h = button->transform->size->height;

    // Vérifie si la position est dans les limites du bouton
    if (x >= btn_x && x <= btn_x + btn_w && y >= btn_y && y <= btn_y + btn_h) {
        button->pressed = 1;  // Bouton pressé
        if (button->on_click) {
            button->on_click(button->data);  // Appeler la fonction on_click avec les données associées
        }
        return 1;  // Bouton pressé
    } else {
        button->pressed = 0;  // Bouton non pressé
        return 0;  // Bouton non pressé
    }
}
