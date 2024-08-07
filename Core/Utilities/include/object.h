#ifndef OBJECT_H
#define OBJECT_H

#include "../../Utilities/include/parse.h"
#include "../../Graphics/include/sprite.h"
#include "../../UI/include/button.h"
#include "../../UI/include/label.h"
#include "../../UI/include/window.h"
#include "../../UI/include/panel.h"
#include "../../UI/include/input.h"
#include "../../UI/include/widget.h"
#include "../../UI/include/tooltip.h"
#include "../../UI/include/image.h"
#include "../../UI/include/progressbar.h"

typedef enum ObjectType {
    OBJECT_TYPE_SPRITE,
    OBJECT_TYPE_IMAGE,
    OBJECT_TYPE_BUTTON,
    OBJECT_TYPE_INPUTFIELD,
    OBJECT_TYPE_LABEL,
    OBJECT_TYPE_PANEL,
    OBJECT_TYPE_TOOLTIP,
    OBJECT_TYPE_WIDGET,
    OBJECT_TYPE_WINDOW,
    OBJECT_TYPE_PROGRESSBAR,
    OBJECT_TYPE_UNKNOWN
} ObjectType;

ObjectType Object_GetType(const char* type_str);
void Object_Set(void* object, const char* params, const char* type_str);    
void Object_ApplyTexture(void* object, Texture* new_texture, const char* type_str);
void Object_Print(void* object, const char* type_object);

#endif // OBJECT_H
