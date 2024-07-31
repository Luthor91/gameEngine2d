#include "../include/widget.h"

Widget* Widget_Init(Transform* transform, Texture* texture) {

    if (!texture) {
        fprintf(stderr, "Widget_Init: texture invalid, default value used\n");
        texture = Texture_Init(NULL, "Assets/Default/DefaultObject.png");
    }

    if (!transform) {
        fprintf(stderr, "Widget_Init: transform invalid, default value used\n");
        transform = Transform_Init(NULL, &(Size2D){DEFAULT_WIDGET_WIDTH, DEFAULT_WIDGET_HEIGHT}, NULL, 0, 0);
    }

    Widget* widget = (Widget*)malloc(sizeof(Widget));
    if (!widget) {
        fprintf(stderr, "Widget_Init: Memory allocation failed for Widget.\n");
        return NULL;
    }

    widget->transform = transform;
    widget->texture = texture;
    widget->is_dragging = 0;

    return widget;
}

void Widget_Set(Widget* widget, const char* params) {
    if (!widget || !params) return;

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
                    Widget_SetPosition(widget, x, y);
                }
            } else if (strcmp(param_name, "size") == 0) {
                int width, height;
                if (sscanf(param_value, "%d,%d", &width, &height) == 2) {
                    Widget_SetSize(widget, width, height);
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
                widget->texture = Texture_Init_Color(NULL, &color, widget->transform->size);
            }  
        }
        param = strtok(NULL, ";");
    }
    free(params_copy);
}


void Widget_SetPosition(Widget* widget, int x, int y) {

    if (x < 0) {
        x = widget->transform->position->x;
    }

    if (y < 0) {
        y = widget->transform->position->y;
    }
    
    widget->transform->position->x = x;
    widget->transform->position->y = y;

}

void Widget_SetSize(Widget* widget, int width, int height) {

    if (width < 0) {
        width = widget->transform->size->width;
    }

    if (height < 0) {
        height = widget->transform->size->height;
    }
    
    widget->transform->size->width = width;
    widget->transform->size->height = height;

}

void Widget_Destroy(Widget* widget) {
    if (widget) {
        free(widget);
    }
}