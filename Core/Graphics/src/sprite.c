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
                char x_str[16], y_str[16];
                if (sscanf(param_value, "%15[^,],%15[^,]", x_str, y_str) == 2) {
                    int x, y;
                    if (strcmp(x_str, "left") == 0) {
                        x = 0;
                    } else if (strcmp(x_str, "right") == 0) {
                        x = DEFAULT_WINDOW_WIDTH - sprite->transform->size->width;
                    } else if (strcmp(x_str, "center") == 0) {
                        x = DEFAULT_WINDOW_WIDTH / 2 - sprite->transform->size->width;
                    } else if (is_percentage(x_str)) {
                        x = parse_percentage(x_str, DEFAULT_WINDOW_WIDTH);
                    } else {
                        x = atoi(x_str);
                    }

                    if (strcmp(y_str, "top") == 0) {
                        y = 0;
                    } else if (strcmp(y_str, "bottom") == 0) {
                        y = DEFAULT_WINDOW_HEIGHT - sprite->transform->size->height;
                    } else if (strcmp(y_str, "center") == 0) {
                        y = DEFAULT_WINDOW_HEIGHT / 2 - sprite->transform->size->height;
                    } else if (is_percentage(y_str)) {
                        y = parse_percentage(y_str, DEFAULT_WINDOW_HEIGHT);
                    } else {
                        y = atoi(y_str);
                    }

                    Sprite_SetPosition(sprite, x, y);
                }
            } else if (strcmp(param_name, "centerposition") == 0) {
                char x_str[16], y_str[16];
                if (sscanf(param_value, "%15[^,],%15[^,]", x_str, y_str) == 2) {
                    int x, y;
                    if (strcmp(x_str, "left") == 0) {
                        x = sprite->transform->size->width / 2;
                    } else if (strcmp(x_str, "right") == 0) {
                        x = DEFAULT_WINDOW_WIDTH - sprite->transform->size->width / 2;
                    } else if (strcmp(x_str, "center") == 0) {
                        x = DEFAULT_WINDOW_WIDTH / 2 - sprite->transform->size->width / 2;
                    } else if (is_percentage(x_str)) {
                        x = parse_percentage(x_str, DEFAULT_WINDOW_WIDTH);
                    } else {
                        x = atoi(x_str);
                    }

                    if (strcmp(y_str, "top") == 0) {
                        y = sprite->transform->size->height / 2;
                    } else if (strcmp(y_str, "bottom") == 0) {
                        y = DEFAULT_WINDOW_HEIGHT - sprite->transform->size->height / 2;
                    } else if (strcmp(y_str, "center") == 0) {
                        y = DEFAULT_WINDOW_HEIGHT / 2 - sprite->transform->size->height / 2;
                    } else if (is_percentage(y_str)) {
                        y = parse_percentage(y_str, DEFAULT_WINDOW_HEIGHT);
                    } else {
                        y = atoi(y_str);
                    }

                    Sprite_SetPosition(sprite, x - sprite->transform->size->width / 2, y - sprite->transform->size->height / 2);
                }
            } else if (strcmp(param_name, "size") == 0) {
                int width, height;
                if (sscanf(param_value, "%d,%d", &width, &height) == 2) {
                    Sprite_SetSize(sprite, width, height);
                }
            } else if (strcmp(param_name, "backgroundcolor") == 0) {
                Color color;
                if (strcmp(param_value, "RED") == 0) {
                    color = (Color){255, 0, 0, 255};
                } else if (strcmp(param_value, "GREEN") == 0) {
                    color = (Color){0, 255, 0, 255};
                } else if (strcmp(param_value, "BLUE") == 0) {
                    color = (Color){0, 0, 255, 255};
                } else if (strcmp(param_value, "WHITE") == 0) {
                    color = (Color){255, 255, 255, 255};
                } else if (strcmp(param_value, "BLACK") == 0) {
                    color = (Color){0, 0, 0, 255};
                } else if (strcmp(param_value, "YELLOW") == 0) {
                    color = (Color){255, 255, 0, 255};
                } else if (strcmp(param_value, "CYAN") == 0) {
                    color = (Color){0, 255, 255, 255};
                } else if (strcmp(param_value, "MAGENTA") == 0) {
                    color = (Color){255, 0, 255, 255};
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
