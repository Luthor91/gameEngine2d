#include "../include/sprite.h"

Sprite* Sprite_Init(Transform* transform, Texture* texture) {

    if (!texture) {
        fprintf(stderr, "Sprite_Init: texture invalid, default value used\n");
        texture = Texture_Init(NULL, "Assets/Default/DefaultObject.png");
    }

    if (!transform) {
        fprintf(stderr, "Sprite_Init: transform invalid, default value used\n");
        transform = Transform_Init(NULL, &(Size2D){DEFAULT_SPRITE_WIDTH, DEFAULT_SPRITE_HEIGHT}, NULL, 0, 0);
    }

    Sprite* sprite = (Sprite*)malloc(sizeof(Sprite));
    if (!sprite) {
        fprintf(stderr, "Sprite_Init: Memory allocation failed for Sprite.\n");
        return NULL;
    }

    sprite->transform = transform;
    sprite->texture = texture;

    return sprite;
}

void Sprite_Set(Sprite* sprite, const char* params) {
    if (!sprite || !params) return;

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
                    Sprite_SetPosition(sprite, x, y);
                }
            } else if (strcmp(param_name, "size") == 0) {
                int width, height;
                if (sscanf(param_value, "%d,%d", &width, &height) == 2) {
                    Sprite_SetSize(sprite, width, height);
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
                sprite->texture = Texture_Init_Color(NULL, &color, sprite->transform->size);
            }  
        }
        param = strtok(NULL, ";");
    }
    free(params_copy);
}

void Sprite_SetPosition(Sprite* sprite, int x, int y) {

    if (x < 0) {
        x = sprite->transform->position->x;
    }

    if (y < 0) {
        y = sprite->transform->position->y;
    }
    
    sprite->transform->position->x = x;
    sprite->transform->position->y = y;

}

void Sprite_SetSize(Sprite* sprite, int width, int height) {

    if (width < 0) {
        width = sprite->transform->size->width;
    }

    if (height < 0) {
        height = sprite->transform->size->height;
    }
    
    sprite->transform->size->width = width;
    sprite->transform->size->height = height;

}

void Sprite_Destroy(Sprite* sprite) {
    SDL_DestroyTexture(sprite->texture->sdl_texture);
    sprite->texture = NULL;
}
