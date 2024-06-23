#include "../include/label.h"

/**************************
    Initialisation du sprite
***************************/

Label* Label_Init(Transform* transform, Font* font, char* text) {  
    
    Label* label = malloc(sizeof(Label));
    if (!label) {
        return NULL;
    }

    if (transform->scale == 0) {
        transform->scale = 1.0;
    }

    label->transform = transform;
    label->font = font;
    label->text = text;

    return label;
}