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
    Object_Set(label, params, "Label");
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