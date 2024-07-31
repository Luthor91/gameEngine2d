#ifndef WIDGET_H
#define WIDGET_H

#include "../../Graphics/include/texture.h"
#include "../../Spatial/include/transform.h"
#include "../../Utilities/include/string.h"
#include "../../Utilities/include/global.h"



typedef struct Widget {
    Transform* transform;
    Texture* texture;
    
    int is_dragging;
    int drag_offset_x;
    int drag_offset_y;
} Widget;

Widget* Widget_Init(Transform* transform, Texture* texture);
void Widget_Set(Widget* widget, const char* params);
void Widget_SetPosition(Widget* widget, int x, int y);
void Widget_SetSize(Widget* widget, int width, int height);
void Widget_Destroy(Widget* widget);

#endif // WIDGET_H