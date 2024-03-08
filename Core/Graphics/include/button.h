#ifndef BUTTON_H
#define BUTTON_H

#include "sprite.h"
#include "transform.h"

typedef struct Button {
    Transform* transform;
    Sprite* sprite;
    int pressed;
    void (*on_click)(void*);
    void* data; 
} Button;
#include "../include/button.h"

Button* Button_Create(int x, int y, int width, int height);
Button* Button_Init(Transform* transform, Sprite* sprite, void (*on_click)(void*), void* data);
Button* Button_InheritSprite(Sprite* sprite, void (*on_click)(void*), void* data);
void Button_Destroy(Button* button);
int Button_SetPosition(Button* button, int x, int y);
int Button_SetSize(Button* button, int width, int height);
int Button_SetSprite(Button* button, Sprite* sprite);
int Button_SetOnClick(Button* button, void (*on_click)(void*), void* data);

int Button_SyncTransformWithSprite(Button* button);
int Button_IsPressed(Button* button, int x, int y);

#endif