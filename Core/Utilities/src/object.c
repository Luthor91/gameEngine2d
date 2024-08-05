#include "../include/object.h"

/**
 * posy = position sur l'axe Y
 * posx = position sur l'axe X
 * cposy = position sur l'axe Y, l'objet sera centré
 * cposx = position sur l'axe X, l'objet sera centré
 */

ObjectType Object_GetType(const char* type_str) {

    if (strcmp(type_str, "Sprite") == 0) {
        return OBJECT_TYPE_SPRITE;
    } else if (strcmp(type_str, "Image") == 0) {
        return OBJECT_TYPE_IMAGE;
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
    Transform* transform = NULL;
    Texture* texture = NULL;
    Font* font = NULL;
    char* text = NULL;
    int max_length = 0;

    switch (type) {
        case OBJECT_TYPE_SPRITE:
            transform = ((Sprite*)object)->transform;
            texture = ((Sprite*)object)->texture;
            break;
        case OBJECT_TYPE_IMAGE:
            transform = ((Image*)object)->transform;
            texture = ((Image*)object)->texture;
            break;
        case OBJECT_TYPE_BUTTON:
            transform = ((Button*)object)->transform;
            texture = ((Button*)object)->texture;
            break;
        case OBJECT_TYPE_INPUTFIELD:
            transform = ((InputField*)object)->transform;
            texture = ((InputField*)object)->texture;
            font = ((InputField*)object)->font;
            text = ((InputField*)object)->text;
            max_length = ((InputField*)object)->max_length;
            break;
        case OBJECT_TYPE_LABEL:
            transform = ((Label*)object)->transform;
            texture = ((Label*)object)->texture;
            font = ((Label*)object)->font;
            text = ((Label*)object)->text;
            max_length = ((Label*)object)->max_length;
            break;
        case OBJECT_TYPE_PANEL:
            transform = ((Panel*)object)->transform;
            texture = ((Panel*)object)->texture;
            break;
        case OBJECT_TYPE_TOOLTIP:
            transform = ((Tooltip*)object)->transform;
            texture = ((Tooltip*)object)->texture;
            font = ((Tooltip*)object)->font;
            text = ((Tooltip*)object)->text;
            max_length = ((Tooltip*)object)->max_length;
            break;
        case OBJECT_TYPE_WIDGET:
            transform = ((Widget*)object)->transform;
            texture = ((Widget*)object)->texture;
            break;
        case OBJECT_TYPE_WINDOW:
            transform = ((Window*)object)->transform;
            texture = ((Window*)object)->texture;
            break;
        default:
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
            Parse_CleanParamName(param_name);

            int x, y, width, height;
            Color* color = Color_Init(0, 0, 0, 0);

            if (strcmp(param_name, "position") == 0) {
                char x_str[16], y_str[16];
                if (sscanf(param_value, "%15[^,],%15[^,]", x_str, y_str) == 2) {
                    x = Parse_Expression(x_str, transform->size->width, "posx");
                    y = Parse_Expression(y_str, transform->size->height, "posy");
                    transform->position = Point2D_Set(transform->position, x, y);
                }
            } else if (strcmp(param_name, "centerposition") == 0) {
                char x_str[16], y_str[16];
                if (sscanf(param_value, "%15[^,],%15[^,]", x_str, y_str) == 2) {
                    x = Parse_Expression(x_str, transform->size->width, "cposx");
                    y = Parse_Expression(y_str, transform->size->height, "cposy");
                    transform->position = Point2D_Set(transform->position, x, y);
                }
            } else if (strcmp(param_name, "size") == 0) {
                char width_str[16], height_str[16];
                if (sscanf(param_value, "%15[^,],%15[^,]", width_str, height_str) == 2) {
                    transform->size->width = Parse_Expression(width_str, transform->size->width, param_name);
                    transform->size->height = Parse_Expression(height_str, transform->size->height, param_name);
                }
            } else if (strcmp(param_name, "backgroundcolor") == 0) {
                if (Parse_Color(color, param_value)) {
                    Texture* new_texture = Texture_Init_Color(NULL, color, NULL);
                    Object_ApplyTexture(object, new_texture, type_str);
                }
            } else if (strcmp(param_name, "textcolor") == 0 && font) {
                if (Parse_Color(color, param_value)) {
                    font->color = color;
                }
            } else if (strcmp(param_name, "textsize") == 0 && font) {
                int size = 0;
                if (sscanf(param_value, "%d", &size) == 1) {
                    font = Font_SetSize(font, size);
                }
            } else if (strcmp(param_name, "text") == 0 && text) {
                strncpy(text, param_value, max_length);
                text[max_length] = '\0';
            }
        }
        param = strtok(NULL, ";");
    }
    free(params_copy);
}

void Object_ApplyTexture(void* object, Texture* new_texture, const char* type_str) {
    if (!object || !new_texture || !type_str) return;

    ObjectType type = Object_GetType(type_str);

    switch (type) {
        case OBJECT_TYPE_SPRITE: {
            Sprite* sprite = (Sprite*)object;
            // Libérer l'ancienne texture si elle existe
            if (sprite->texture) {
                Texture_Destroy(sprite->texture);
            }
            // Appliquer la nouvelle texture
            sprite->texture = new_texture;
            break;
        }
        case OBJECT_TYPE_IMAGE: {
            Image* image = (Image*)object;
            if (image->texture) {
                Texture_Destroy(image->texture);
            }
            image->texture = new_texture;
            break;
        }
        case OBJECT_TYPE_BUTTON: {
            Button* button = (Button*)object;
            if (button->texture) {
                Texture_Destroy(button->texture);
            }
            button->texture = new_texture;
            break;
        }
        case OBJECT_TYPE_PANEL: {
            Panel* panel = (Panel*)object;
            if (panel->texture) {
                Texture_Destroy(panel->texture);
            }
            panel->texture = new_texture;
            break;
        }
        case OBJECT_TYPE_TOOLTIP: {
            Tooltip* tooltip = (Tooltip*)object;
            if (tooltip->texture) {
                Texture_Destroy(tooltip->texture);
            }
            tooltip->texture = new_texture;
            break;
        }
        case OBJECT_TYPE_WIDGET: {
            Widget* widget = (Widget*)object;
            if (widget->texture) {
                Texture_Destroy(widget->texture);
            }
            widget->texture = new_texture;
            break;
        }
        case OBJECT_TYPE_WINDOW: {
            Window* window = (Window*)object;
            if (window->texture) {
                Texture_Destroy(window->texture);
            }
            window->texture = new_texture;
            break;
        }
        default:
            printf("Object_ApplyTexture : Type d'objet inconnu.\n");
            break;
    }
}
