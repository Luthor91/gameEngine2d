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
    if (!button || !params) return;

    char* params_copy = strdup(params);
    if (!params_copy) return;

    char* param = strtok(params_copy, ";");
    while (param != NULL) {
        char* delimiter_pos = strchr(param, ':');
        if (delimiter_pos) {
            *delimiter_pos = '\0';
            char* param_name = param;
            char* param_value = delimiter_pos + 1;
            clean_param_name(param_name);

            if (strcmp(param_name, "position") == 0) {
                int x, y;
                if (sscanf(param_value, "%d,%d", &x, &y) == 2) {
                    Button_SetPosition(button, x, y);
                }
            } else if (strcmp(param_name, "size") == 0) {
                int width, height;
                if (sscanf(param_value, "%d,%d", &width, &height) == 2) {
                    Button_SetSize(button, width, height);
                }
            } else if (strcmp(param_name, "backgroundcolor") == 0) {
                Color color;
                if (strcmp(param_value, "RED") == 0) {
                    color = COLOR_RED;
                } else if (strcmp(param_value, "GREEN") == 0) {
                    color = COLOR_GREEN;
                } else if (strcmp(param_value, "BLUE") == 0) {
                    color = COLOR_BLUE;
                } else if (strcmp(param_value, "WHITE") == 0) {
                    color = COLOR_WHITE;
                } else if (strcmp(param_value, "BLACK") == 0) {
                    color = COLOR_BLACK;
                } else if (strcmp(param_value, "YELLOW") == 0) {
                    color = COLOR_YELLOW;
                } else if (strcmp(param_value, "CYAN") == 0) {
                    color = COLOR_CYAN;
                } else if (strcmp(param_value, "MAGENTA") == 0) {
                    color = COLOR_MAGENTA;
                } else if (sscanf(param_value, "%hhd,%hhd,%hhd,%hhd", &color.r, &color.g, &color.b, &color.a) == 4) {
                    // Successfully parsed RGBA color
                } else {
                    // Handle invalid color format if necessary
                    free(params_copy);
                    return;
                }
                button->texture = Texture_Init_Color(NULL, &color, button->transform->size);
            } 
        }
        param = strtok(NULL, ";");
    }
    free(params_copy);
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