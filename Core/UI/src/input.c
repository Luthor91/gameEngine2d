#include "../include/input.h"

InputField* InputField_Init(Transform* transform, Texture* texture, Font* font) {

    if (texture == NULL) {
        fprintf(stderr, "InputField_Init: texture invalid, default value used\n");
        texture = Texture_Init(NULL, "Assets/Default/DefaultPanel.png");
    }

    if (transform == NULL) {
        fprintf(stderr, "InputField_Init: transform invalid, default value used\n");
        transform = Transform_Init(NULL, &(Size2D){DEFAULT_INPUT_WIDTH, DEFAULT_INPUT_HEIGHT}, NULL, 0, 0);
    }

    if (font == NULL) {
        fprintf(stderr, "InputField_Init: font invalid, default value used\n");
        font = Font_Init(NULL, NULL, DEFAULT_FONT_SIZE);
    }

    InputField* input_field = (InputField*)malloc(sizeof(InputField));
    if (input_field == NULL) {
        printf("InputField_Init: Échec de l'allocation de mémoire pour le champ de saisie.\n");
        return NULL;
    }

    input_field->texture = texture;
    input_field->transform = transform;
    input_field->text = (char*)malloc(DEFAULT_MAX_LENGHT_INPUT + 1);
    if (input_field->text == NULL) {
        printf("InputField_Init: Échec de l'allocation de mémoire pour le texte.\n");
        free(input_field);
        return NULL;
    }
    input_field->text[0] = '\0';
    input_field->font = font;
    input_field->max_length = DEFAULT_MAX_LENGHT_INPUT;
    input_field->cursor_position = 0;
    input_field->is_focused = 0;

    return input_field;
}

void InputField_Set(InputField* input_field, const char* params) {
    if (!input_field || !params) return;

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
                    InputField_SetPosition(input_field, x, y);
                }
            } else if (strcmp(param_name, "size") == 0) {
                int width, height;
                if (sscanf(param_value, "%d,%d", &width, &height) == 2) {
                    InputField_SetSize(input_field, width, height);
                }
            } else if (strcmp(param_name, "text") == 0) {
                InputField_SetText(input_field, param_value);
            } else if (strcmp(param_name, "textsize") == 0) {
                int size;
                if (sscanf(param_value, "%d", &size) == 1) {
                    InputField_SetTextSize(input_field, size);
                }
            } else if (strcmp(param_name, "textcolor") == 0) {
                Color* text_color = Color_Init(0, 0, 0, 0);
                if (strcmp(param_value, "RED") == 0) {
                    *text_color = COLOR_RED;
                } else if (strcmp(param_value, "GREEN") == 0) {
                    *text_color = COLOR_GREEN;
                } else if (strcmp(param_value, "BLUE") == 0) {
                    *text_color = COLOR_BLUE;
                } else if (strcmp(param_value, "WHITE") == 0) {
                    *text_color = COLOR_WHITE;
                } else if (strcmp(param_value, "BLACK") == 0) {
                    *text_color = COLOR_BLACK;
                } else if (strcmp(param_value, "YELLOW") == 0) {
                    *text_color = COLOR_YELLOW;
                } else if (strcmp(param_value, "CYAN") == 0) {
                    *text_color = COLOR_CYAN;
                } else if (strcmp(param_value, "MAGENTA") == 0) {
                    *text_color = COLOR_MAGENTA;
                } else if (sscanf(param_value, "%hhd,%hhd,%hhd,%hhd", &text_color->r, &text_color->g, &text_color->b, &text_color->a) == 4) {
                    // Successfully parsed RGBA color
                } else {
                    // Handle invalid color format if necessary
                    free(params_copy);
                    return;
                }
                // Copier les valeurs de couleur directement dans la couleur de la police du label
                input_field->font->color = text_color;

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
                input_field->texture = Texture_Init_Color(NULL, &color, input_field->transform->size);
            }  
        }
        param = strtok(NULL, ";");
    }
    free(params_copy);
}


void InputField_SetText(InputField* input_field, const char* text) {
    strncpy(input_field->text, text, input_field->max_length);
    input_field->text[input_field->max_length] = '\0'; // S'assurer que le texte est null-terminated
}

void InputField_SetTextSize(InputField* input_field, int size) {
    if (!input_field || size <= 0) return;

    TTF_CloseFont(input_field->font->sdl_font);
    input_field->font->sdl_font = TTF_OpenFont(input_field->font->path, size);
    if (!input_field->font->sdl_font) {
        printf("InputField_SetTextSize : Échec de la modification de la taille du texte: %s\n", TTF_GetError());
    }
}

void InputField_SetTextColor(InputField* input_field, Color color) {
    if (!input_field) return;
    input_field->font->color = &color;
}

void InputField_SetSize(InputField* input_field, int width, int height) {

    if (width < 0) {
        width = input_field->transform->size->width;
    }

    if (height < 0) {
        height = input_field->transform->size->height;
    }
    
    input_field->transform->size->width = width;
    input_field->transform->size->height = height;

}

void InputField_SetPosition(InputField* input_field, int x, int y) {

    if (x < 0) {
        x = input_field->transform->position->x;
    }

    if (y < 0) {
        y = input_field->transform->position->y;
    }
    
    input_field->transform->position->x = x;
    input_field->transform->position->y = y;

}