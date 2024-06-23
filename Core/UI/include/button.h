#ifndef BUTTON_H
#define BUTTON_H

#include <stdlib.h>
#include "../../Spatial/include/transform.h"
#include "../../Graphics/include/texture.h"

typedef struct Button {
    Transform* transform;
    Texture* texture;
    int pressed;
    void (*on_click)(void*);
    void* data; 
} Button;

Button* Button_Init(Transform* aspect, Texture* texture, void (*on_click)(void*), void* data);
void Button_Destroy(Button* button);
int Button_SetOnClick(Button* button, void (*on_click)(void*), void* data);
int Button_IsPressed(Button* button, Point2D* position);

#endif