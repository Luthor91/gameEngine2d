#include "../include/label.h"

Label* Label_Init(Transform* transform, Texture* texture, Font* font, char* text) {

    if (texture == NULL) {
        fprintf(stderr, "Label_Init: texture invalid, default value used\n");
        texture = Texture_Init(NULL, "Assets/Default/DefaultPanel.png");
    }

    if (transform == NULL) {
        fprintf(stderr, "Label_Init: transform invalid, default value used\n");
        transform = Transform_Init(NULL, &(Size2D){DEFAULT_LABEL_WIDTH, DEFAULT_LABEL_HEIGHT}, NULL, 0, 0);
    }

    if (font == NULL) {
        fprintf(stderr, "Label_Init: font invalid, default value used\n");
        font = Font_Init(NULL, NULL, DEFAULT_FONT_SIZE);
    }

    Label* label = (Label*)malloc(sizeof(Label));
    if (label == NULL) {
        printf("Label_Init: Échec de l'allocation de mémoire pour le champ de saisie.\n");
        return NULL;
    }

    label->texture = texture;
    label->transform = transform;
    label->font = font;

    label->text = strdup(text);
    if (label->text == NULL) {
        printf("Label_Init: Échec de l'allocation de mémoire pour le texte.\n");
        free(label);
        return NULL;
    }

    CheckTextFit(label->font, label->text, label->transform->size->width - 5, label->transform->size->height);

    return label;
}

void Label_Set(Label* label, const char* params) {
    if (!label || !params) return;

    // Créer une copie mutable de la chaîne de paramètres
    char* params_copy = strdup(params);
    if (!params_copy) return;

    // Parcourir chaque paramètre séparé par des points-virgules
    char* param = strtok(params_copy, ";");
    while (param != NULL) {
        // Diviser le paramètre en nom et valeur
        char* delimiter_pos = strchr(param, ':');
        if (delimiter_pos) {
            *delimiter_pos = '\0';
            char* param_name = param;
            char* param_value = delimiter_pos + 1;

            // Nettoyer le nom du paramètre
            clean_param_name(param_name);

            // Traiter chaque nom de paramètre
            if (strcmp(param_name, "position") == 0) {
                int x, y;
                if (sscanf(param_value, "%d,%d", &x, &y) == 2) {
                    Label_SetPosition(label, x, y);
                }
                
            } else if (strcmp(param_name, "size") == 0) {
                int width, height;
                if (sscanf(param_value, "%d,%d", &width, &height) == 2) {
                    Label_SetSize(label, width, height);
                }

            } else if (strcmp(param_name, "text") == 0) {
                Label_SetText(label, param_value);

            } else if (strcmp(param_name, "textsize") == 0) {
                int size;
                if (sscanf(param_value, "%d", &size) == 1) {
                    Label_SetTextSize(label, size);
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
                label->font->color = text_color;

            } else if (strcmp(param_name, "backgroundcolor") == 0) {
                Color background_color;
                if (strcmp(param_value, "RED") == 0) {
                    background_color = COLOR_RED;
                } else if (strcmp(param_value, "GREEN") == 0) {
                    background_color = COLOR_GREEN;
                } else if (strcmp(param_value, "BLUE") == 0) {
                    background_color = COLOR_BLUE;
                } else if (strcmp(param_value, "WHITE") == 0) {
                    background_color = COLOR_WHITE;
                } else if (strcmp(param_value, "BLACK") == 0) {
                    background_color = COLOR_BLACK;
                } else if (strcmp(param_value, "YELLOW") == 0) {
                    background_color = COLOR_YELLOW;
                } else if (strcmp(param_value, "CYAN") == 0) {
                    background_color = COLOR_CYAN;
                } else if (strcmp(param_value, "MAGENTA") == 0) {
                    background_color = COLOR_MAGENTA;
                } else if (sscanf(param_value, "%hhd,%hhd,%hhd,%hhd", &background_color.r, &background_color.g, &background_color.b, &background_color.a) == 4) {
                    // Successfully parsed RGBA color
                } else {
                    // Handle invalid color format if necessary
                    free(params_copy);
                    return;
                }
                label->texture = Texture_Init_Color(NULL, &background_color, label->transform->size);
            }
        }

        // Passer au paramètre suivant
        param = strtok(NULL, ";");
    }

    free(params_copy);
}

void Label_SetText(Label* label, const char* text) {
    strncpy(label->text, text, label->max_length);
    label->text[label->max_length] = '\0'; // S'assurer que le texte est null-terminated
    CheckTextFit(label->font, label->text, label->transform->size->width - 5, label->transform->size->height);
}

void Label_SetTextSize(Label* label, int size) {
    if (!label || size <= 0) return;

    TTF_CloseFont(label->font->sdl_font);
    label->font->sdl_font = TTF_OpenFont(label->font->path, size);
    if (!label->font->sdl_font) {
        printf("Label_SetTextSize : Échec de la modification de la taille du texte: %s\n", TTF_GetError());
    }
}

void Label_SetTextColor(Label* label, Color color) {
    if (!label) return;
    printf("Setting color: R=%d, G=%d, B=%d, A=%d\n", color.r, color.g, color.b, color.a);
    label->font->color = NULL;
    label->font->color = &color;
}

void Label_SetPosition(Label* label, int x, int y) {

    if (x < 0) {
        x = label->transform->position->x;
    }

    if (y < 0) {
        y = label->transform->position->y;
    }
    
    label->transform->position->x = x;
    label->transform->position->y = y;

}

void Label_SetSize(Label* label, int width, int height) {

    if (width < 0) {
        width = label->transform->size->width;
    }

    if (height < 0) {
        height = label->transform->size->height;
    }
    
    label->transform->size->width = width;
    label->transform->size->height = height;

}