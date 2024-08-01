#include "../include/panel.h"

Panel* Panel_Init(Transform* transform, Texture* texture) {

    if (!texture) {
        fprintf(stderr, "Panel_Init: texture invalid, default value used\n");
        texture = Texture_Init(NULL, "Assets/Default/DefaultPanel.png");
    }

    if (!transform) {
        fprintf(stderr, "Panel_Init: transform invalid, default value used\n");
        transform = Transform_Init(NULL, &(Size2D){DEFAULT_PANEL_WIDTH, DEFAULT_PANEL_HEIGHT}, NULL, 0, 0);
    }

    Panel* panel = (Panel*)malloc(sizeof(Panel));
    if (!panel) {
        fprintf(stderr, "Panel_Init: Memory allocation failed for Panel.\n");
        return NULL;
    }

    panel->transform = transform;
    panel->texture = texture;

    return panel;
}

void Panel_Set(Panel* panel, const char* params) {
    Object_Set(panel, params, "Panel");
}

void Panel_SetPosition(Panel* panel, int x, int y) {

    if (x < 0) {
        x = panel->transform->position->x;
    }

    if (y < 0) {
        y = panel->transform->position->y;
    }
    
    panel->transform->position->x = x;
    panel->transform->position->y = y;

}

void Panel_SetSize(Panel* panel, int width, int height) {

    if (width < 0) {
        width = panel->transform->size->width;
    }

    if (height < 0) {
        height = panel->transform->size->height;
    }
    
    panel->transform->size->width = width;
    panel->transform->size->height = height;

}