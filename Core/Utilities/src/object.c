#include "../include/object.h"

ObjectType Object_GetType(const char* type_str) {

    if (strcmp(type_str, "Sprite") == 0) {
        return OBJECT_TYPE_SPRITE;
    } else if (strcmp(type_str, "Button") == 0) {
        return OBJECT_TYPE_BUTTON;
    } else if (strcmp(type_str, "InputField") == 0) {
        return OBJECT_TYPE_INPUTFIELD;
    } else if (strcmp(type_str, "Label") == 0) {
        return OBJECT_TYPE_LABEL;
    } else if (strcmp(type_str, "Panel") == 0) {
        return OBJECT_TYPE_PANEL;
    } else if (strcmp(type_str, "Tooltip") == 0) {
        return OBJECT_TYPE_TOOLTIP;
    } else if (strcmp(type_str, "Widget") == 0) {
        return OBJECT_TYPE_WIDGET;
    } else if (strcmp(type_str, "Window") == 0) {
        return OBJECT_TYPE_WINDOW;
    }
    // Type non reconnu
    return OBJECT_TYPE_UNKNOWN;
}

void Object_Set(void* object, const char* params, const char* type_str) {
    if (!object || !params) return;

    ObjectType type = Object_GetType(type_str);

    // Déclaration de pointeurs pour les types spécifiques
    Sprite* sprite = NULL;
    Button* button = NULL;
    InputField* inputfield = NULL;
    Label* label = NULL;
    Panel* panel = NULL;
    Tooltip* tooltip = NULL;
    Widget* widget = NULL;
    Window* window = NULL;

    // Détection du type via enum
    switch (type) {
        case OBJECT_TYPE_SPRITE:
            sprite = (Sprite*)object;
            break;
        case OBJECT_TYPE_BUTTON:
            button = (Button*)object;
            break;
        case OBJECT_TYPE_INPUTFIELD:
            inputfield = (InputField*)object;
            break;
        case OBJECT_TYPE_LABEL:
            label = (Label*)object;
            break;
        case OBJECT_TYPE_PANEL:
            panel = (Panel*)object;
            break;
        case OBJECT_TYPE_TOOLTIP:
            tooltip = (Tooltip*)object;
            break;
        case OBJECT_TYPE_WIDGET:
            widget = (Widget*)object;
            break;
        case OBJECT_TYPE_WINDOW:
            window = (Window*)object;
            break;
        default:
            // Type non pris en charge
            return;
    }

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

            // Déclaration de variables spécifiques pour chaque type
            int x, y, width, height;
            Color* color = Color_Init(0, 0, 0, 0);

            if (strcmp(param_name, "position") == 0) {
                char x_str[16], y_str[16];
                if (sscanf(param_value, "%15[^,],%15[^,]", x_str, y_str) == 2) {
                    if (strcmp(x_str, "left") == 0) {
                        x = 0;
                    } else if (strcmp(x_str, "right") == 0) {
                        x = (sprite ? DEFAULT_WINDOW_WIDTH - sprite->transform->size->width :
                            (button ? DEFAULT_WINDOW_WIDTH - button->transform->size->width :
                            (inputfield ? DEFAULT_WINDOW_WIDTH - inputfield->transform->size->width :
                            (label ? DEFAULT_WINDOW_WIDTH - label->transform->size->width : 
                            (panel ? DEFAULT_WINDOW_WIDTH - panel->transform->size->width :
                            (tooltip ? DEFAULT_WINDOW_WIDTH - tooltip->transform->size->width :
                            (widget ? DEFAULT_WINDOW_WIDTH - widget->transform->size->width :
                            (window ? DEFAULT_WINDOW_WIDTH - window->transform->size->width : 0
                            ))))))));
                    } else if (strcmp(x_str, "center") == 0) {
                        x = (sprite ? DEFAULT_WINDOW_WIDTH / 2 - sprite->transform->size->width :
                            (button ? DEFAULT_WINDOW_WIDTH / 2 - button->transform->size->width :
                            (inputfield ? DEFAULT_WINDOW_WIDTH / 2 - inputfield->transform->size->width :
                            (label ? DEFAULT_WINDOW_WIDTH / 2 - label->transform->size->width : 
                            (panel ? DEFAULT_WINDOW_WIDTH / 2 - panel->transform->size->width :
                            (tooltip ? DEFAULT_WINDOW_WIDTH / 2 - tooltip->transform->size->width :
                            (widget ? DEFAULT_WINDOW_WIDTH / 2 - widget->transform->size->width :
                            (window ? DEFAULT_WINDOW_WIDTH / 2 - window->transform->size->width : 0
                            ))))))));
                    } else if (is_percentage(x_str)) {
                        x = parse_percentage(x_str, DEFAULT_WINDOW_WIDTH);
                    } else {
                        x = atoi(x_str);
                    }

                    if (strcmp(y_str, "top") == 0) {
                        y = 0;
                    } else if (strcmp(y_str, "bottom") == 0) {
                        y = (sprite ? DEFAULT_WINDOW_HEIGHT - sprite->transform->size->height :
                            (button ? DEFAULT_WINDOW_HEIGHT - button->transform->size->height :
                            (inputfield ? DEFAULT_WINDOW_HEIGHT - inputfield->transform->size->height :
                            (label ? DEFAULT_WINDOW_HEIGHT - label->transform->size->height : 
                            (panel ? DEFAULT_WINDOW_HEIGHT - panel->transform->size->height :
                            (tooltip ? DEFAULT_WINDOW_HEIGHT - tooltip->transform->size->height :
                            (widget ? DEFAULT_WINDOW_HEIGHT - widget->transform->size->height :
                            (window ? DEFAULT_WINDOW_HEIGHT - window->transform->size->height : 0
                            ))))))));
                    } else if (strcmp(y_str, "center") == 0) {
                        y = (sprite ? DEFAULT_WINDOW_HEIGHT / 2 - sprite->transform->size->height :
                            (button ? DEFAULT_WINDOW_HEIGHT / 2 - button->transform->size->height :
                            (inputfield ? DEFAULT_WINDOW_HEIGHT / 2 - inputfield->transform->size->height :
                            (label ? DEFAULT_WINDOW_HEIGHT / 2 - label->transform->size->height : 
                            (panel ? DEFAULT_WINDOW_HEIGHT / 2 - panel->transform->size->height :
                            (tooltip ? DEFAULT_WINDOW_HEIGHT / 2 - tooltip->transform->size->height :
                            (widget ? DEFAULT_WINDOW_HEIGHT / 2 - widget->transform->size->height :
                            (window ? DEFAULT_WINDOW_HEIGHT / 2 - window->transform->size->height : 0
                            ))))))));
                    } else if (is_percentage(y_str)) {
                        y = parse_percentage(y_str, DEFAULT_WINDOW_HEIGHT);
                    } else {
                        y = atoi(y_str);
                    }

                    if (sprite) {
                        sprite->transform->position = Point2D_Set(sprite->transform->position, x, y);
                    } else if (button) {
                        button->transform->position = Point2D_Set(button->transform->position, x, y);
                    } else if (inputfield) {
                        inputfield->transform->position = Point2D_Set(inputfield->transform->position, x, y);
                    } else if (label) {
                        label->transform->position = Point2D_Set(label->transform->position, x, y);
                    } else if (panel) {
                        panel->transform->position = Point2D_Set(panel->transform->position, x, y);
                    } else if (tooltip) {
                        tooltip->transform->position = Point2D_Set(tooltip->transform->position, x, y);
                    } else if (widget) {
                        widget->transform->position = Point2D_Set(widget->transform->position, x, y);
                    } else if (window) {
                        window->transform->position = Point2D_Set(window->transform->position, x, y);
                    }
                }
            } else if (strcmp(param_name, "centerposition") == 0) {
                char x_str[16], y_str[16];
                if (sscanf(param_value, "%15[^,],%15[^,]", x_str, y_str) == 2) {
                    if (strcmp(x_str, "left") == 0) {
                        x = (sprite ? sprite->transform->size->width / 2 :
                            (button ? button->transform->size->width / 2 :
                            (inputfield ? inputfield->transform->size->width / 2 :
                            (label ? label->transform->size->width / 2 : 
                            (panel ? panel->transform->size->width / 2 :
                            (tooltip ? tooltip->transform->size->width / 2 :
                            (widget ? widget->transform->size->width / 2  :
                            (window ? window->transform->size->width / 2 : 0
                            ))))))));
                    } else if (strcmp(x_str, "right") == 0) {
                        x = (sprite ? DEFAULT_WINDOW_WIDTH - sprite->transform->size->width / 2 :
                            (button ? DEFAULT_WINDOW_WIDTH - button->transform->size->width / 2 :
                            (inputfield ? DEFAULT_WINDOW_WIDTH - inputfield->transform->size->width / 2 :
                            (label ? DEFAULT_WINDOW_WIDTH - label->transform->size->width / 2 : 
                            (panel ? DEFAULT_WINDOW_WIDTH - panel->transform->size->width / 2 :
                            (tooltip ? DEFAULT_WINDOW_WIDTH - tooltip->transform->size->width / 2 :
                            (widget ? DEFAULT_WINDOW_WIDTH - widget->transform->size->width / 2  :
                            (window ? DEFAULT_WINDOW_WIDTH - window->transform->size->width / 2 : 0
                            ))))))));
                    } else if (strcmp(x_str, "center") == 0) {
                        x = (sprite ? DEFAULT_WINDOW_WIDTH / 2 - sprite->transform->size->width / 2 :
                            (button ? DEFAULT_WINDOW_WIDTH / 2 - button->transform->size->width / 2 :
                            (inputfield ? DEFAULT_WINDOW_WIDTH / 2 - inputfield->transform->size->width / 2 :
                            (label ? DEFAULT_WINDOW_WIDTH / 2 - label->transform->size->width / 2 : 
                            (panel ? DEFAULT_WINDOW_WIDTH / 2 - panel->transform->size->width / 2 :
                            (tooltip ? DEFAULT_WINDOW_WIDTH / 2 - tooltip->transform->size->width / 2 :
                            (widget ? DEFAULT_WINDOW_WIDTH / 2 - widget->transform->size->width / 2 :
                            (window ? DEFAULT_WINDOW_WIDTH / 2 - window->transform->size->width / 2 : 0
                            ))))))));
                    } else if (is_percentage(x_str)) {
                        x = parse_percentage(x_str, DEFAULT_WINDOW_WIDTH);
                    } else {
                        x = atoi(x_str);
                    }

                    if (strcmp(y_str, "top") == 0) {
                        y = (sprite ? sprite->transform->size->height / 2 :
                            (button ? button->transform->size->height / 2 :
                            (inputfield ? inputfield->transform->size->height / 2 :
                            (label ? label->transform->size->height / 2 : 
                            (panel ? panel->transform->size->height / 2 :
                            (tooltip ? tooltip->transform->size->height / 2 :
                            (widget ? widget->transform->size->height / 2 :
                            (window ? window->transform->size->height / 2 : 0
                            ))))))));
                    } else if (strcmp(y_str, "bottom") == 0) {
                        y = (sprite ? DEFAULT_WINDOW_HEIGHT - sprite->transform->size->height / 2 :
                            (button ? DEFAULT_WINDOW_HEIGHT - button->transform->size->height / 2 :
                            (inputfield ? DEFAULT_WINDOW_HEIGHT - inputfield->transform->size->height / 2 :
                            (label ? DEFAULT_WINDOW_HEIGHT - label->transform->size->height / 2 : 
                            (panel ? DEFAULT_WINDOW_HEIGHT - panel->transform->size->height / 2 :
                            (tooltip ? DEFAULT_WINDOW_HEIGHT - tooltip->transform->size->height / 2 :
                            (widget ? DEFAULT_WINDOW_HEIGHT - widget->transform->size->height / 2 :
                            (window ? DEFAULT_WINDOW_HEIGHT - window->transform->size->height / 2 : 0
                            ))))))));
                    } else if (strcmp(y_str, "center") == 0) {
                        y = (sprite ? DEFAULT_WINDOW_HEIGHT / 2 - sprite->transform->size->height / 2 :
                            (button ? DEFAULT_WINDOW_HEIGHT / 2 - button->transform->size->height / 2 :
                            (inputfield ? DEFAULT_WINDOW_HEIGHT / 2 - inputfield->transform->size->height / 2 :
                            (label ? DEFAULT_WINDOW_HEIGHT / 2 - label->transform->size->height / 2 : 
                            (panel ? DEFAULT_WINDOW_HEIGHT / 2 - panel->transform->size->height / 2 :
                            (tooltip ? DEFAULT_WINDOW_HEIGHT / 2 - tooltip->transform->size->height / 2 :
                            (widget ? DEFAULT_WINDOW_HEIGHT / 2 - widget->transform->size->height / 2 :
                            (window ? DEFAULT_WINDOW_HEIGHT / 2 - window->transform->size->height / 2 : 0
                            ))))))));
                    }else if (is_percentage(y_str)) {
                        y = parse_percentage(y_str, DEFAULT_WINDOW_HEIGHT);
                    } else {
                        y = atoi(y_str);
                    }

                    if (sprite) {
                        sprite->transform->position = Point2D_Set(sprite->transform->position, x, y);
                    } else if (button) {
                        button->transform->position = Point2D_Set(button->transform->position, x, y);
                    } else if (inputfield) {
                        inputfield->transform->position = Point2D_Set(inputfield->transform->position, x, y);
                    } else if (label) {
                        label->transform->position = Point2D_Set(label->transform->position, x, y);
                    } else if (panel) {
                        panel->transform->position = Point2D_Set(panel->transform->position, x, y);
                    } else if (tooltip) {
                        tooltip->transform->position = Point2D_Set(tooltip->transform->position, x, y);
                    } else if (widget) {
                        widget->transform->position = Point2D_Set(widget->transform->position, x, y);
                    } else if (window) {
                        window->transform->position = Point2D_Set(window->transform->position, x, y);
                    }
                }
            } else if (strcmp(param_name, "size") == 0) {
                if (sscanf(param_value, "%d,%d", &width, &height) == 2) {
                    if (sprite) {
                        sprite->transform->size->width = width;
                        sprite->transform->size->height = height;
                    } else if (button) {
                        button->transform->size->width = width;
                        button->transform->size->height = height;
                    } else if (inputfield) {
                        inputfield->transform->size->width = width;
                        inputfield->transform->size->height = height;
                    } else if (label) {
                        label->transform->size->width = width;
                        label->transform->size->height = height;
                    } else if (panel) {
                        panel->transform->size->width = width;
                        panel->transform->size->height = height;
                    } else if (tooltip) {
                        tooltip->transform->size->width = width;
                        tooltip->transform->size->height = height;
                    } else if (widget) {
                        widget->transform->size->width = width;
                        widget->transform->size->height = height;
                    } else if (window) {
                        window->transform->size->width = width;
                        window->transform->size->height = height;
                    }
                }
            } else if (strcmp(param_name, "backgroundcolor") == 0) {
                if (Color_Parsing(color, param_value)) {
                    if (sprite) {
                        sprite->texture = Texture_Init_Color(NULL, color, NULL);
                    } else if (button) {
                        button->texture = Texture_Init_Color(NULL, color, NULL);
                    } else if (inputfield) {
                        inputfield->texture = Texture_Init_Color(NULL, color, NULL);
                    } else if (label) {
                        label->texture = Texture_Init_Color(NULL, color, NULL);
                    } else if (panel) {
                        panel->texture = Texture_Init_Color(NULL, color, NULL);
                    } else if (tooltip) {
                        tooltip->texture = Texture_Init_Color(NULL, color, NULL);
                    } else if (widget) {
                        widget->texture = Texture_Init_Color(NULL, color, NULL);
                    } else if (window) {
                        window->texture = Texture_Init_Color(NULL, color, NULL);
                    }
                }
            } else if (strcmp(param_name, "textcolor") == 0) {
                if (Color_Parsing(color, param_value)) {
                     if (inputfield) {
                        inputfield->font->color = color;
                    } else if (label) {
                        label->font->color = color;
                    } else if (tooltip) {
                        tooltip->font->color = color;
                    }
                }
            } else if (strcmp(param_name, "textsize") == 0) {
                int size = 0;
                if (sscanf(param_value, "%d", &size) == 1) {
                    if (inputfield) {
                        inputfield->font = Font_SetSize(inputfield->font, size);
                    } else if (label) {
                        label->font = Font_SetSize(label->font, size);
                    } else if (tooltip) {
                        tooltip->font = Font_SetSize(tooltip->font, size);
                    }
                }
            } else if (strcmp(param_name, "text") == 0) {
                if (inputfield) {
                    strncpy(inputfield->text, param_value, inputfield->max_length);
                    inputfield->text[inputfield->max_length] = '\0';
                } else if (label) {
                    strncpy(label->text, param_value, label->max_length);
                    label->text[label->max_length] = '\0';
                } else if (tooltip) {
                    strncpy(tooltip->text, param_value, tooltip->max_length);
                    tooltip->text[tooltip->max_length] = '\0';
                }
            }
        }
        param = strtok(NULL, ";");
    }
    free(params_copy);
}
