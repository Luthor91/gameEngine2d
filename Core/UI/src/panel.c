#include "../include/panel.h"

Panel* Panel_Init(Transform* transform, Texture* texture) {

    if (!texture) {
        fprintf(stderr, "Panel_Init: texture invalid, default value used\n");
        texture = Texture_Init(NULL, "Assets/Default/DefaultPanel.png");
    }

    if (!transform) {
        fprintf(stderr, "Panel_Init: transform invalid, default value used\n");
        transform = Transform_Init(NULL, &(Size2D){DEFAULT_PANEL_WIDTH, DEFAULT_PANEL_HEIGHT}, NULL, 0, 0);
    }

    Panel* panel = (Panel*)malloc(sizeof(Panel));
    if (!panel) {
        fprintf(stderr, "Panel_Init: Memory allocation failed for Panel.\n");
        return NULL;
    }

    panel->transform = transform;
    panel->texture = texture;

    return panel;
}

void Panel_Set(Panel* panel, const char* params) {
    if (!panel || !params) return;

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
                    Panel_SetPosition(panel, x, y);
                }
            } else if (strcmp(param_name, "size") == 0) {
                int width, height;
                if (sscanf(param_value, "%d,%d", &width, &height) == 2) {
                    Panel_SetSize(panel, width, height);
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
                panel->texture = Texture_Init_Color(NULL, &color, panel->transform->size);
            }  
        }
        param = strtok(NULL, ";");
    }
    free(params_copy);
}

void Panel_SetPosition(Panel* panel, int x, int y) {

    if (x < 0) {
        x = panel->transform->position->x;
    }

    if (y < 0) {
        y = panel->transform->position->y;
    }
    
    panel->transform->position->x = x;
    panel->transform->position->y = y;

}

void Panel_SetSize(Panel* panel, int width, int height) {

    if (width < 0) {
        width = panel->transform->size->width;
    }

    if (height < 0) {
        height = panel->transform->size->height;
    }
    
    panel->transform->size->width = width;
    panel->transform->size->height = height;

}