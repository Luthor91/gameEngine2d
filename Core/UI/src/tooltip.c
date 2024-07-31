#include "../include/tooltip.h"


Tooltip* Tooltip_Init(Transform* transform, Texture* texture, Area2D* hitbox, Font* font, const char* initial_text) {
    if (texture == NULL) {
        fprintf(stderr, "Tooltip_Init: texture invalid, default value used\n");
        texture = Texture_Init(NULL, "Assets/Default/DefaultPanel.png");
    }

    if (transform == NULL) {
        fprintf(stderr, "Tooltip_Init: transform invalid, default value used\n");
        transform = Transform_Init(NULL, &(Size2D){DEFAULT_TOOLTIP_WIDTH, DEFAULT_TOOLTIP_HEIGHT}, NULL, 0, 0);
    }

    if (hitbox == NULL) {
        fprintf(stderr, "Tooltip_Init: area invalid, default value used\n");
        hitbox = Area2D_Init(transform->position, transform->size);
    }

    if (font == NULL) {
        fprintf(stderr, "Tooltip_Init: font invalid, default value used\n");
        font = Font_Init(NULL, NULL, DEFAULT_FONT_SIZE);
    }

    Tooltip* tooltip = (Tooltip*)malloc(sizeof(Tooltip));
    if (tooltip == NULL) {
        printf("Tooltip_Init: Échec de l'allocation de mémoire pour le tooltip.\n");
        return NULL;
    }

    tooltip->texture = texture;
    tooltip->transform = transform;
    tooltip->hitbox = hitbox;
    tooltip->font = font;
    tooltip->max_length = DEFAULT_MAX_LENGHT_TOOLTIP;
    tooltip->is_visible = 0;
    tooltip->offset = Vector2_Init(5, 5);

    if (initial_text == NULL) {
        initial_text = "";
    }

    tooltip->text = strdup(initial_text);
    if (tooltip->text == NULL) {
        printf("Tooltip_Init: Échec de l'allocation de mémoire pour le texte.\n");
        free(tooltip);
        return NULL;
    }

    CheckTextFit(tooltip->font, tooltip->text, tooltip->transform->size->width, tooltip->transform->size->height);

    return tooltip;
}

void Tooltip_Set(Tooltip* tooltip, const char* params) {
    if (!tooltip || !params) return;

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
                    Tooltip_SetPosition(tooltip, x, y);
                }
            } else if (strcmp(param_name, "size") == 0) {
                int width, height;
                if (sscanf(param_value, "%d,%d", &width, &height) == 2) {
                    Tooltip_SetSize(tooltip, width, height);
                }
            } else if (strcmp(param_name, "text") == 0) {
                Tooltip_SetText(tooltip, param_value);
            } else if (strcmp(param_name, "textsize") == 0) {
                int size;
                if (sscanf(param_value, "%d", &size) == 1) {
                    Tooltip_SetTextSize(tooltip, size);
                }
            } else if (strcmp(param_name, "textcolor") == 0) {
                printf("Tooltip_Set: textcolor\n");
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
                tooltip->font->color = text_color;

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
                tooltip->texture = Texture_Init_Color(NULL, &color, tooltip->transform->size);
            } 
        }
        param = strtok(NULL, ";");
    }
    free(params_copy);
}


void Tooltip_SetText(Tooltip* tooltip, const char* text) {
    strncpy(tooltip->text, text, tooltip->max_length);
    tooltip->text[tooltip->max_length] = '\0'; // S'assurer que le texte est null-terminated

    CheckTextFit(tooltip->font, tooltip->text, tooltip->transform->size->width, tooltip->transform->size->height);
}

void Tooltip_SetTextSize(Tooltip* tooltip, int size) {
    if (!tooltip || size <= 0) return;

    TTF_CloseFont(tooltip->font->sdl_font);
    tooltip->font->sdl_font = TTF_OpenFont(tooltip->font->path, size);
    if (!tooltip->font->sdl_font) {
        printf("Tooltip_SetTextSize : Échec de la modification de la taille du texte: %s\n", TTF_GetError());
    }
}

void Tooltip_SetTextColor(Tooltip* tooltip, Color color) {
    if (!tooltip) return;
    tooltip->font->color = &color;
}

void Tooltip_SetPosition(Tooltip* tooltip, int x, int y) {

    if (x < 0) {
        x = tooltip->transform->position->x;
    }

    if (y < 0) {
        y = tooltip->transform->position->y;
    }
    
    tooltip->transform->position->x = x;
    tooltip->transform->position->y = y;

}

void Tooltip_SetSize(Tooltip* tooltip, int width, int height) {

    if (width < 0) {
        width = tooltip->transform->size->width;
    }

    if (height < 0) {
        height = tooltip->transform->size->height;
    }
    
    tooltip->transform->size->width = width;
    tooltip->transform->size->height = height;

}