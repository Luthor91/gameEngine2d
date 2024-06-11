#ifndef LABEL_H
#define LABEL_H

#include "../../Spatial/include/transform.h"
#include "font.h"

typedef struct Label {
    Transform* transform;
    Font* font;
    char* text;
} Label;

/**************************
    Initialisation du label
***************************/

Label* Label_Init(Transform* transform, Font* font, char* text);

#endif // LABEL_H
