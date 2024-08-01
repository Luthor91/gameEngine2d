#include "../include/widget.h"

Widget* Widget_Init(Transform* transform, Texture* texture) {

    if (!texture) {
        fprintf(stderr, "Widget_Init: texture invalid, default value used\n");
        texture = Texture_Init(NULL, "Assets/Default/DefaultObject.png");
    }

    if (!transform) {
        fprintf(stderr, "Widget_Init: transform invalid, default value used\n");
        transform = Transform_Init(NULL, &(Size2D){DEFAULT_WIDGET_WIDTH, DEFAULT_WIDGET_HEIGHT}, NULL, 0, 0);
    }

    Widget* widget = (Widget*)malloc(sizeof(Widget));
    if (!widget) {
        fprintf(stderr, "Widget_Init: Memory allocation failed for Widget.\n");
        return NULL;
    }

    widget->transform = transform;
    widget->texture = texture;
    widget->is_dragging = 0;

    return widget;
}

void Widget_Set(Widget* widget, const char* params) {
    Object_Set(widget, params, "Widget");
}

void Widget_SetPosition(Widget* widget, int x, int y) {

    if (x < 0) {
        x = widget->transform->position->x;
    }

    if (y < 0) {
        y = widget->transform->position->y;
    }
    
    widget->transform->position->x = x;
    widget->transform->position->y = y;

}

void Widget_SetSize(Widget* widget, int width, int height) {

    if (width < 0) {
        width = widget->transform->size->width;
    }

    if (height < 0) {
        height = widget->transform->size->height;
    }
    
    widget->transform->size->width = width;
    widget->transform->size->height = height;

}

void Widget_Destroy(Widget* widget) {
    if (widget) {
        free(widget);
    }
}