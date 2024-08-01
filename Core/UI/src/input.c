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
    Object_Set(input_field, params, "InputField");
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